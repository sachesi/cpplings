#include "cpplings_test.hpp"

#include <type_traits>

class Fraction {
public:
    Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

    explicit operator double() const {
        return static_cast<double>(numerator_) / static_cast<double>(denominator_);
    }

    // An explicit `operator bool` is still used in conditions like `if` and `!`.
    explicit operator bool() const {
        return numerator_ != 0;
    }

private:
    int numerator_;
    int denominator_;
};

TEST(to_double) {
    CHECK_NEAR(static_cast<double>(Fraction(1, 4)), 0.25, 1e-9);
    CHECK_NEAR(static_cast<double>(Fraction(-3, 2)), -1.5, 1e-9);
}

TEST(as_condition) {
    CHECK(Fraction(1, 3));
    CHECK(!Fraction(0, 5));
}

TEST(no_implicit_conversions) {
    static_assert(!std::is_convertible_v<Fraction, double>);
    static_assert(!std::is_convertible_v<Fraction, bool>);
    static_assert(!std::is_convertible_v<Fraction, int>);
}
