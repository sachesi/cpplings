#include "info_file.hpp"

#include <charconv>
#include <format>
#include <stdexcept>
#include <unordered_set>

namespace {

std::string_view trim(std::string_view s) {
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r')) {
        s.remove_prefix(1);
    }
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r')) {
        s.remove_suffix(1);
    }
    return s;
}

class Parser {
public:
    explicit Parser(std::string_view text) : text_(text) {}

    InfoFile parse() {
        InfoFile info;
        ExerciseInfo* exercise = nullptr;

        while (pos_ < text_.size()) {
            std::string_view line = trim(next_line());
            if (line.empty() || line.front() == '#') {
                continue;
            }
            if (line == "[[exercises]]") {
                exercise = &info.exercises.emplace_back();
                continue;
            }

            std::size_t eq = line.find('=');
            if (eq == std::string_view::npos) {
                fail("expected `key = value`");
            }
            std::string_view key = trim(line.substr(0, eq));
            std::string_view rest = trim(line.substr(eq + 1));

            if (exercise == nullptr) {
                if (key == "format_version") {
                    info.format_version = parse_int(rest);
                } else if (key == "welcome_message") {
                    info.welcome_message = parse_string(rest);
                } else if (key == "final_message") {
                    info.final_message = parse_string(rest);
                } else {
                    fail(std::format("unknown key `{}`", key));
                }
                continue;
            }

            if (key == "name") {
                exercise->name = parse_string(rest);
            } else if (key == "dir") {
                exercise->dir = parse_string(rest);
            } else if (key == "hint") {
                exercise->hint = parse_string(rest);
            } else if (key == "strict") {
                exercise->strict = parse_bool(rest);
            } else if (key == "sanitizer") {
                exercise->sanitizer = parse_string(rest);
            } else if (key == "skip_check_unsolved") {
                exercise->skip_check_unsolved = parse_bool(rest);
            } else {
                fail(std::format("unknown exercise key `{}`", key));
            }
        }

        std::unordered_set<std::string> names;
        for (const ExerciseInfo& e : info.exercises) {
            if (e.name.empty() || e.dir.empty()) {
                throw std::runtime_error("info.toml: every exercise needs a `name` and a `dir`");
            }
            if (!names.insert(e.name).second) {
                throw std::runtime_error(std::format("info.toml: duplicate exercise name `{}`", e.name));
            }
        }
        return info;
    }

private:
    std::string_view text_;
    std::size_t pos_ = 0;
    int line_no_ = 0;

    std::string_view next_line() {
        std::size_t end = text_.find('\n', pos_);
        if (end == std::string_view::npos) {
            end = text_.size();
        }
        std::string_view line = text_.substr(pos_, end - pos_);
        pos_ = end + 1;
        ++line_no_;
        return line;
    }

    [[noreturn]] void fail(std::string_view message) const {
        throw std::runtime_error(std::format("info.toml:{}: {}", line_no_, message));
    }

    int parse_int(std::string_view s) const {
        int value = 0;
        auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
        if (ec != std::errc{} || ptr != s.data() + s.size()) {
            fail("expected an integer");
        }
        return value;
    }

    bool parse_bool(std::string_view s) const {
        if (s == "true") {
            return true;
        }
        if (s == "false") {
            return false;
        }
        fail("expected `true` or `false`");
    }

    // Handles "basic" and """multi-line""" strings starting at `s`.
    std::string parse_string(std::string_view s) {
        if (s.starts_with("\"\"\"")) {
            return parse_multiline(s.substr(3));
        }
        if (s.size() < 2 || s.front() != '"') {
            fail("expected a string");
        }
        std::string out;
        std::size_t i = 1;
        for (; i < s.size() && s[i] != '"'; ++i) {
            if (s[i] == '\\') {
                append_escape(out, s, i);
            } else {
                out += s[i];
            }
        }
        if (i != s.size() - 1) {
            fail("unterminated string or trailing characters");
        }
        return out;
    }

    std::string parse_multiline(std::string_view first) {
        std::string raw;
        std::string_view line = first;
        // A newline right after the opening delimiter is trimmed.
        bool first_line = true;
        while (true) {
            std::size_t close = find_closing(line);
            if (close != std::string_view::npos) {
                raw += line.substr(0, close);
                if (!trim(line.substr(close + 3)).empty()) {
                    fail("trailing characters after a multi-line string");
                }
                break;
            }
            if (!(first_line && line.empty())) {
                raw += line;
                raw += '\n';
            }
            first_line = false;
            if (pos_ >= text_.size()) {
                fail("unterminated multi-line string");
            }
            line = next_line();
        }

        std::string out;
        for (std::size_t i = 0; i < raw.size(); ++i) {
            if (raw[i] == '\\') {
                if (i + 1 < raw.size() && raw[i + 1] == '\n') {
                    // Line-ending backslash: skip the newline and leading whitespace.
                    i += 2;
                    while (i < raw.size() && (raw[i] == ' ' || raw[i] == '\t' || raw[i] == '\n')) {
                        ++i;
                    }
                    --i;
                    continue;
                }
                append_escape(out, raw, i);
            } else {
                out += raw[i];
            }
        }
        return out;
    }

    static std::size_t find_closing(std::string_view line) {
        for (std::size_t i = 0; i + 3 <= line.size(); ++i) {
            if (line.substr(i, 3) == "\"\"\"" && (i == 0 || line[i - 1] != '\\')) {
                return i;
            }
        }
        return std::string_view::npos;
    }

    void append_escape(std::string& out, std::string_view s, std::size_t& i) const {
        if (i + 1 >= s.size()) {
            fail("dangling backslash");
        }
        char c = s[++i];
        switch (c) {
        case 'n':
            out += '\n';
            break;
        case 't':
            out += '\t';
            break;
        case '"':
            out += '"';
            break;
        case '\\':
            out += '\\';
            break;
        default:
            fail(std::format("unsupported escape `\\{}`", c));
        }
    }
};

} // namespace

InfoFile InfoFile::parse(std::string_view text) {
    return Parser(text).parse();
}
