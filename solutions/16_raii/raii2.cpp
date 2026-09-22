#include "cpplings_test.hpp"

#include <algorithm>
#include <cstddef>
#include <utility>

class Buffer {
public:
    explicit Buffer(std::size_t size) : size_(size), data_(new int[size]{}) {}

    ~Buffer() { delete[] data_; }

    Buffer(const Buffer& other) : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // Copy-and-swap: `other` is already a copy, and the old data is freed when
    // `other` is destroyed. This is also correct for `b = b`.
    Buffer& operator=(Buffer other) {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
        return *this;
    }

    std::size_t size() const { return size_; }
    int get(std::size_t index) const { return data_[index]; }
    void set(std::size_t index, int value) { data_[index] = value; }

private:
    std::size_t size_;
    int* data_;
};

// With the rule of zero, the class stores a `std::vector<int>` and doesn't need
// a destructor or copy operations at all.

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
