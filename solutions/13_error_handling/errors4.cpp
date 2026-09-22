#include "cpplings_test.hpp"

#include <expected>

enum class CreationError { Negative, Zero };

class PositiveNonzeroInteger {
public:
    static std::expected<PositiveNonzeroInteger, CreationError> create(long value) {
        if (value < 0) {
            return std::unexpected(CreationError::Negative);
        }
        if (value == 0) {
            return std::unexpected(CreationError::Zero);
        }
        return PositiveNonzeroInteger(value);
    }

    long value() const { return value_; }

private:
    explicit PositiveNonzeroInteger(long value) : value_(value) {}

    long value_;
};

TEST(valid_value) {
    auto result = PositiveNonzeroInteger::create(10);
    CHECK(result.has_value());
    CHECK_EQ(result->value(), 10);
}

TEST(negative_value) {
    auto result = PositiveNonzeroInteger::create(-10);
    CHECK(!result.has_value());
    CHECK_EQ(result.error(), CreationError::Negative);
}

TEST(zero) {
    auto result = PositiveNonzeroInteger::create(0);
    CHECK(!result.has_value());
    CHECK_EQ(result.error(), CreationError::Zero);
}
