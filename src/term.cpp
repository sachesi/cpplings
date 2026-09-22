#include "term.hpp"

#include <poll.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <format>
#include <iostream>

namespace term {

namespace {

termios original_termios{};
volatile std::sig_atomic_t termios_modified = 0;
volatile std::sig_atomic_t full_screen_active = 0;
volatile std::sig_atomic_t resized = 0;

constexpr std::string_view enter_full_screen = "\x1b[?1049h\x1b[?25l\x1b[?7l\x1b[?1000h\x1b[?1006h";
constexpr std::string_view leave_full_screen = "\x1b[?1006l\x1b[?1000l\x1b[?7h\x1b[?25h\x1b[?1049l";

std::string pending_input;

void write_all(int fd, std::string_view text) {
    while (!text.empty()) {
        ssize_t n = ::write(fd, text.data(), text.size());
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            return;
        }
        text.remove_prefix(static_cast<std::size_t>(n));
    }
}

extern "C" void handle_terminating_signal(int sig) {
    if (full_screen_active) {
        write_all(STDOUT_FILENO, leave_full_screen);
    }
    if (termios_modified) {
        ::tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    }
    std::signal(sig, SIG_DFL);
    std::raise(sig);
}

extern "C" void handle_resize(int) {
    resized = 1;
}

// Reads whatever is available without blocking longer than `timeout_ms`.
bool fill_pending(int timeout_ms) {
    pollfd pfd{STDIN_FILENO, POLLIN, 0};
    int ready = ::poll(&pfd, 1, timeout_ms);
    if (ready <= 0) {
        return false;
    }
    char buf[256];
    ssize_t n = ::read(STDIN_FILENO, buf, sizeof buf);
    if (n <= 0) {
        return false;
    }
    pending_input.append(buf, static_cast<std::size_t>(n));
    return true;
}

Key parse_escape_sequence() {
    // pending_input starts with ESC.
    if (pending_input.size() == 1 && !fill_pending(30)) {
        pending_input.clear();
        return {KeyCode::Esc};
    }

    char kind = pending_input[1];
    if (kind != '[' && kind != 'O') {
        pending_input.erase(0, 1);
        return {KeyCode::Esc};
    }

    std::size_t end = 2;
    while (true) {
        while (end < pending_input.size()) {
            unsigned char c = static_cast<unsigned char>(pending_input[end]);
            if (c >= 0x40 && c <= 0x7e) {
                break;
            }
            ++end;
        }
        if (end < pending_input.size() || !fill_pending(30)) {
            break;
        }
    }
    if (end >= pending_input.size()) {
        pending_input.clear();
        return {KeyCode::Esc};
    }

    std::string params = pending_input.substr(2, end - 2);
    char final_byte = pending_input[end];
    pending_input.erase(0, end + 1);

    if (!params.empty() && params.front() == '<') {
        // SGR mouse report: <button;x;y(M|m)
        int button = std::atoi(params.c_str() + 1);
        if (final_byte == 'M' && button == 64) {
            return {KeyCode::ScrollUp};
        }
        if (final_byte == 'M' && button == 65) {
            return {KeyCode::ScrollDown};
        }
        return {};
    }

    switch (final_byte) {
    case 'A':
        return {KeyCode::Up};
    case 'B':
        return {KeyCode::Down};
    case 'H':
        return {KeyCode::Home};
    case 'F':
        return {KeyCode::End};
    case '~':
        if (params == "1" || params == "7") {
            return {KeyCode::Home};
        }
        if (params == "4" || params == "8") {
            return {KeyCode::End};
        }
        return {};
    default:
        return {};
    }
}

} // namespace

void write_stdout(std::string_view text) {
    std::cout.flush();
    write_all(STDOUT_FILENO, text);
}

bool stdout_is_terminal() {
    return ::isatty(STDOUT_FILENO) && ::isatty(STDIN_FILENO);
}

Size size() {
    winsize ws{};
    if (::ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0 || ws.ws_col == 0) {
        return {80, 24};
    }
    return {ws.ws_col, ws.ws_row};
}

void clear(std::string& out) {
    out += "\x1b[H\x1b[2J\x1b[3J";
}

void progress_bar(std::string& out, int progress, int total, int term_width) {
    constexpr std::string_view prefix = "Progress: [";
    constexpr int wrapper_width = static_cast<int>(prefix.size() + std::string_view("] xxx/xxx").size());
    constexpr int min_line_width = wrapper_width + 4;

    if (term_width < min_line_width) {
        out += std::format("Progress: {}/{}", progress, total);
        return;
    }

    out += prefix;
    int width = term_width - wrapper_width;
    int filled = total > 0 ? width * progress / total : 0;

    out += green;
    out.append(static_cast<std::size_t>(filled), '#');
    if (filled < width) {
        out += '>';
        if (width - filled > 1) {
            out += red;
            out.append(static_cast<std::size_t>(width - filled - 1), '-');
        }
    }
    out += default_fg;
    out += std::format("] {:>3}/{}", progress, total);
}

void file_link(std::string& out, std::string_view path, std::string_view canonical_path) {
    if (canonical_path.empty()) {
        out += path;
        return;
    }
    out += "\x1b]8;;file://";
    out += canonical_path;
    out += "\x1b\\";
    out += path;
    out += "\x1b]8;;\x1b\\";
}

std::string canonicalize(const std::string& path) {
    char* resolved = ::realpath(path.c_str(), nullptr);
    if (resolved == nullptr) {
        return {};
    }
    std::string result = resolved;
    std::free(resolved);
    return result;
}

void press_enter_prompt() {
    std::cout.flush();
    std::string line;
    std::getline(std::cin, line);
    write_stdout("\n");
}

bool take_resize_event() {
    if (resized) {
        resized = 0;
        return true;
    }
    return false;
}

void install_signal_handlers() {
    struct sigaction terminate{};
    terminate.sa_handler = handle_terminating_signal;
    sigemptyset(&terminate.sa_mask);
    ::sigaction(SIGINT, &terminate, nullptr);
    ::sigaction(SIGTERM, &terminate, nullptr);
    ::sigaction(SIGHUP, &terminate, nullptr);

    // No SA_RESTART: a resize must interrupt poll() so the screen is redrawn.
    struct sigaction winch{};
    winch.sa_handler = handle_resize;
    sigemptyset(&winch.sa_mask);
    ::sigaction(SIGWINCH, &winch, nullptr);
}

Key read_key(int timeout_ms) {
    if (pending_input.empty() && !fill_pending(timeout_ms)) {
        return {};
    }

    unsigned char c = static_cast<unsigned char>(pending_input.front());
    if (c == 0x1b) {
        return parse_escape_sequence();
    }
    pending_input.erase(0, 1);

    if (c == '\r' || c == '\n') {
        return {KeyCode::Enter};
    }
    if (c == 0x7f || c == 0x08) {
        return {KeyCode::Backspace};
    }
    return {KeyCode::Char, static_cast<char>(c)};
}

void discard_pending_input() {
    pending_input.clear();
    ::tcflush(STDIN_FILENO, TCIFLUSH);
}

InputMode::InputMode(Kind kind) {
    if (::tcgetattr(STDIN_FILENO, &previous_) != 0) {
        return;
    }
    if (!termios_modified) {
        original_termios = previous_;
    }

    termios modified = original_termios;
    modified.c_lflag &= ~static_cast<tcflag_t>(ICANON | ECHO);
    if (kind == Kind::Raw) {
        modified.c_lflag &= ~static_cast<tcflag_t>(ISIG | IEXTEN);
        modified.c_iflag &= ~static_cast<tcflag_t>(IXON | ICRNL);
    }
    modified.c_cc[VMIN] = 1;
    modified.c_cc[VTIME] = 0;

    if (::tcsetattr(STDIN_FILENO, TCSANOW, &modified) == 0) {
        outermost_ = !termios_modified;
        termios_modified = 1;
        active_ = true;
    }
}

InputMode::~InputMode() {
    if (active_) {
        ::tcsetattr(STDIN_FILENO, TCSANOW, &previous_);
        if (outermost_) {
            termios_modified = 0;
        }
    }
}

FullScreen::FullScreen() {
    write_stdout(enter_full_screen);
    full_screen_active = 1;
}

FullScreen::~FullScreen() {
    write_stdout(leave_full_screen);
    full_screen_active = 0;
}

} // namespace term
