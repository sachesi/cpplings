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

    Planet earth{"Earth", sun};
    CHECK_EQ(sun.use_count(), 4);

    {
        Planet mars{"Mars", sun};
        CHECK_EQ(sun.use_count(), 5);
    }
    CHECK_EQ(sun.use_count(), 4);

    mercury.sun.reset();
    CHECK_EQ(sun.use_count(), 3);
    CHECK(mercury.sun == nullptr);
    CHECK(venus.sun == sun);
}
