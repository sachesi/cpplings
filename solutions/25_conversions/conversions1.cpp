#include "cpplings_test.hpp"

#include <charconv>
#include <string>
#include <string_view>
#include <type_traits>

struct Person {
    std::string name = "John";
    int age = 30;

    Person() = default;

    explicit Person(std::string_view text) {
        std::size_t comma = text.find(',');
        if (comma == std::string_view::npos || text.find(',', comma + 1) != std::string_view::npos) {
            return;
        }

        std::string_view name_part = text.substr(0, comma);
        std::string_view age_part = text.substr(comma + 1);
        if (name_part.empty()) {
            return;
        }

        int parsed_age = 0;
        auto [end, error] = std::from_chars(age_part.data(), age_part.data() + age_part.size(), parsed_age);
        if (error != std::errc{} || end != age_part.data() + age_part.size()) {
            return;
        }

        name = name_part;
        age = parsed_age;
    }
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
