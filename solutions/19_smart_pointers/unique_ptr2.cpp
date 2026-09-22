#include "cpplings_test.hpp"

#include <memory>

int alive_sensors = 0;

struct Sensor {
    Sensor() { ++alive_sensors; }
    ~Sensor() { --alive_sensors; }
    int read() const { return 42; }
};

int measure(bool needs_calibration) {
    // Deleted on every path out of the function.
    auto sensor = std::make_unique<Sensor>();
    if (needs_calibration) {
        return -1;
    }
    return sensor->read();
}

TEST(measurement) {
    CHECK_EQ(measure(false), 42);
    CHECK_EQ(alive_sensors, 0);
}

TEST(calibration_needed) {
    CHECK_EQ(measure(true), -1);
    CHECK_EQ(alive_sensors, 0);
}
