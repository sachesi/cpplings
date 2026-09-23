#include "cpplings_test.hpp"

#include <algorithm>
#include <string>
#include <vector>

struct Person {
    std::string name;
    int age;
};

void sort_people(std::vector<Person>& people) {
    std::ranges::sort(people, [](const Person& a, const Person& b) {
        if (a.age != b.age) {
            return a.age > b.age;
        }
        return a.name < b.name;
    });
}

std::vector<std::string> names(const std::vector<Person>& people) {
    std::vector<std::string> result;
    for (const Person& person : people) {
        result.push_back(person.name);
    }
    return result;
}

TEST(oldest_first) {
    std::vector<Person> people = {{"Ada", 36}, {"Alan", 41}, {"Grace", 85}};
    sort_people(people);
    CHECK_EQ(names(people), (std::vector<std::string>{"Grace", "Alan", "Ada"}));
}

TEST(same_age_sorted_by_name) {
    std::vector<Person> people = {{"Linus", 30}, {"Dennis", 30}, {"Ken", 45}, {"Bjarne", 30}};
    sort_people(people);
    CHECK_EQ(names(people), (std::vector<std::string>{"Ken", "Bjarne", "Dennis", "Linus"}));
}
