// The constructor from a string converts text into a `Person`.

#include "cpplings_test.hpp"

#include <charconv>
#include <string>
#include <string_view>
#include <type_traits>

struct Person {
    std::string name = "John";
    int age = 30;

    Person() = default;

    // TODO: Complete this constructor. The text has the form "Mark,20":
    // 1. Split the text on the comma. If there is not exactly one comma, keep
    //    the default person.
    // 2. If the name is empty, keep the default person.
    // 3. Parse the age with `std::from_chars`. If that fails or doesn't use all
    //    characters, keep the default person.
    // 4. Otherwise, set the name and the age.
    // The conversion should also be explicit: `Person p = "Mark,20";` shouldn't
    // compile.
    Person(std::string_view text) {}
};

TEST(default_person) {
    Person dp;
    CHECK_EQ(dp.name, "John");
    CHECK_EQ(dp.age, 30);
}

TEST(bad_convert) {
    Person p("");
    CHECK_EQ(p.name, "John");
    CHECK_EQ(p.age, 30);
}

TEST(good_convert) {
    Person p("Mark,20");
    CHECK_EQ(p.name, "Mark");
    CHECK_EQ(p.age, 20);
}

TEST(bad_age) {
    Person p("Mark,twenty");
    CHECK_EQ(p.name, "John");
    CHECK_EQ(p.age, 30);
}

TEST(missing_comma_and_age) {
    Person p("Mark");
    CHECK_EQ(p.name, "John");
    CHECK_EQ(p.age, 30);
}

TEST(missing_name) {
    Person p(",1");
    CHECK_EQ(p.name, "John");
    CHECK_EQ(p.age, 30);
}

TEST(trailing_comma) {
    Person p("Mike,32,");
    CHECK_EQ(p.name, "John");
    CHECK_EQ(p.age, 30);
}

TEST(conversion_is_explicit) {
    static_assert(std::is_constructible_v<Person, std::string_view>);
    static_assert(!std::is_convertible_v<std::string_view, Person>);
}
