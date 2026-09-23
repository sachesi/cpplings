#include "cpplings_test.hpp"

// TODO: Fix the compiler errors. Everything in a `class` is private until an
// access specifier says otherwise. Make the constructor and the member functions
// usable from outside, while `celsius_` should stay private.
class Temperature {
    double celsius_;

    explicit Temperature(double celsius) : celsius_(celsius) {}

    double celsius() const { return celsius_; }

    double fahrenheit() const {
        // TODO: Return the temperature in degrees Fahrenheit (°C × 9/5 + 32).
        return 0.0;
    }
};

TEST(boiling_water) {
    Temperature boiling(100.0);
    CHECK_NEAR(boiling.celsius(), 100.0, 1e-9);
    CHECK_NEAR(boiling.fahrenheit(), 212.0, 1e-9);
}

TEST(freezing_water) {
    Temperature freezing(0.0);
    CHECK_NEAR(freezing.fahrenheit(), 32.0, 1e-9);
}
