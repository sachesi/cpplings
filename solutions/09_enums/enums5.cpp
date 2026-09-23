#include "cpplings_test.hpp"

// The names of an `enum class` stay inside the enum.
enum class Color { Red, Green, Blue };
enum class TrafficLight { Red, Yellow, Green };

TrafficLight next(TrafficLight light) {
    switch (light) {
    case TrafficLight::Red:
        return TrafficLight::Green;
    case TrafficLight::Yellow:
        return TrafficLight::Red;
    case TrafficLight::Green:
        return TrafficLight::Yellow;
    }
    return TrafficLight::Red;
}

bool is_warm(Color color) {
    return color == Color::Red;
}

TEST(traffic_light_cycle) {
    CHECK_EQ(next(TrafficLight::Red), TrafficLight::Green);
    CHECK_EQ(next(TrafficLight::Green), TrafficLight::Yellow);
    CHECK_EQ(next(TrafficLight::Yellow), TrafficLight::Red);
}

TEST(warm_colors) {
    CHECK(is_warm(Color::Red));
    CHECK(!is_warm(Color::Blue));
}
