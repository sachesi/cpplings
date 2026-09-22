#include "cpplings_test.hpp"

#include <string>

class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string sound() const { return "..."; }
};

class Dog : public Animal {
public:
    // TODO: This was meant to override `Animal::sound`, but it doesn't. Add
    // `override` to let the compiler tell you why, then fix it.
    std::string sound() { return "Woof!"; }
};

std::string make_noise(const Animal& animal) {
    return animal.sound();
}

TEST(dog_barks) {
    Dog dog;
    CHECK_EQ(make_noise(dog), "Woof!");
}
