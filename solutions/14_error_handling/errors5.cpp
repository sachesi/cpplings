#include "cpplings_test.hpp"

#include <charconv>
#include <expected>
#include <string>
#include <string_view>

std::expected<long, std::string> parse_long(std::string_view text) {
    long value = 0;
    auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (error != std::errc{} || end != text.data() + text.size()) {
        return std::unexpected("not a number: " + std::string(text));
    }
    return value;
}

class PositiveNonzeroInteger {
public:
    static std::expected<PositiveNonzeroInteger, std::string> create(long value) {
        if (value < 0) {
            return std::unexpected("negative");
        }
        if (value == 0) {
            return std::unexpected("zero");
        }
        return PositiveNonzeroInteger(value);
    }

    long value() const { return value_; }

private:
    explicit PositiveNonzeroInteger(long value) : value_(value) {}

    long value_;
};

std::expected<PositiveNonzeroInteger, std::string> parse_pos_nonzero(std::string_view text) {
    // `and_then` only calls `create` if parsing succeeded. Otherwise, the parse
    // error is passed on. Both steps must have the same error type.
    return parse_long(text).and_then(PositiveNonzeroInteger::create);
}

TEST(parse_error) {
    auto result = parse_pos_nonzero("not a number");
    CHECK(!result.has_value());
    CHECK_EQ(result.error(), "not a number: not a number");
}

TEST(negative) {
    auto result = parse_pos_nonzero("-555");
    CHECK(!result.has_value());
    CHECK_EQ(result.error(), "negative");
}

TEST(zero) {
    auto result = parse_pos_nonzero("0");
    CHECK(!result.has_value());
    CHECK_EQ(result.error(), "zero");
}

TEST(positive) {
    auto result = parse_pos_nonzero("42");
    CHECK(result.has_value());
    CHECK_EQ(result->value(), 42);
}
