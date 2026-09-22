#include "cpplings_test.hpp"

#include <string>

class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string sound() const { return "..."; }
};

class Dog : public Animal {
public:
    // The signature must match exactly, including `const`.
    std::string sound() const override { return "Woof!"; }
};

std::string make_noise(const Animal& animal) {
    return animal.sound();
}

TEST(dog_barks) {
    Dog dog;
    CHECK_EQ(make_noise(dog), "Woof!");
}
