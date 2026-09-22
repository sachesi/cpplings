#include "cpplings_test.hpp"

class Temperature {
public:
    explicit Temperature(double celsius) : celsius_(celsius) {}

    double celsius() const { return celsius_; }

    double fahrenheit() const {
        return celsius_ * 9.0 / 5.0 + 32.0;
    }

private:
    double celsius_;
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
