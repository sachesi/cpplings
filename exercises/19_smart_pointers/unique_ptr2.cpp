#include "cpplings_test.hpp"

#include <memory>

int alive_sensors = 0;

struct Sensor {
    Sensor() { ++alive_sensors; }
    ~Sensor() { --alive_sensors; }
    int read() const { return 42; }
};

// Returns the measurement, or -1 if the sensor needs calibration.
// TODO: The sensor is leaked when the function returns early. Let a
// `std::unique_ptr` own it, and remove `new` and `delete`.
int measure(bool needs_calibration) {
    Sensor* sensor = new Sensor();
    if (needs_calibration) {
        return -1;
    }
    int value = sensor->read();
    delete sensor;
    return value;
}

TEST(measurement) {
    CHECK_EQ(measure(false), 42);
    CHECK_EQ(alive_sensors, 0);
}

TEST(calibration_needed) {
    CHECK_EQ(measure(true), -1);
    CHECK_EQ(alive_sensors, 0);
}
