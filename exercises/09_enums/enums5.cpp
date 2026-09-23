#include "cpplings_test.hpp"

// TODO: The names of a plain `enum` are placed in the surrounding scope, so both
// enums below declare `Red` and `Green` at the same place. Fix the compiler
// errors without renaming any value.
enum Color { Red, Green, Blue };
enum TrafficLight { Red, Yellow, Green };

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
