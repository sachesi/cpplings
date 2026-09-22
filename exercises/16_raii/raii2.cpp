#include "cpplings_test.hpp"

#include <cstddef>

// A buffer of integers that manages its memory by hand.
class Buffer {
public:
    explicit Buffer(std::size_t size) : size_(size), data_(new int[size]{}) {}

    ~Buffer() { delete[] data_; }

    // TODO: The compiler-generated copy operations copy the pointer, so two
    // buffers share the same memory and both delete it. Implement a copy
    // constructor and a copy assignment operator that copy the elements.

    std::size_t size() const { return size_; }
    int get(std::size_t index) const { return data_[index]; }
    void set(std::size_t index, int value) { data_[index] = value; }

private:
    std::size_t size_;
    int* data_;
};

TEST(copies_are_independent) {
    Buffer original(3);
    Buffer copy = original;
    copy.set(0, 42);
    CHECK_EQ(original.get(0), 0);
    CHECK_EQ(copy.get(0), 42);
}

TEST(copy_assignment) {
    Buffer a(2);
    Buffer b(5);
    a.set(1, 7);
    b = a;
    a.set(1, 8);
    CHECK_EQ(b.size(), 2);
    CHECK_EQ(b.get(1), 7);
}
