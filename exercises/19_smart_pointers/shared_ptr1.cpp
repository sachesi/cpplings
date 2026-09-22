// In this exercise, we want to express the concept of multiple owners via the
// `std::shared_ptr` type. This is a model of our solar system - there is a
// `Sun` type and multiple `Planet`s. The planets take ownership of the sun,
// indicating that they revolve around the sun.

#include "cpplings_test.hpp"

#include <memory>
#include <string>

struct Sun {};

struct Planet {
    std::string name;
    std::shared_ptr<Sun> sun;
};

TEST(shared_ptr1) {
    auto sun = std::make_shared<Sun>();
    CHECK_EQ(sun.use_count(), 1);

    Planet mercury{"Mercury", sun};
    CHECK_EQ(sun.use_count(), 2);

    Planet venus{"Venus", sun};
    CHECK_EQ(sun.use_count(), 3);

    // TODO: All planets should share the same sun.
    Planet earth{"Earth", std::make_shared<Sun>()};
    CHECK_EQ(sun.use_count(), 4);

    {
        // TODO: Create Mars sharing the sun. It only exists inside these braces.
        CHECK_EQ(sun.use_count(), 5);
    }
    CHECK_EQ(sun.use_count(), 4);

    // TODO: Mercury gives up its sun. Reset its pointer.
    CHECK_EQ(sun.use_count(), 3);
    CHECK(mercury.sun == nullptr);
    CHECK(venus.sun == sun);
}
