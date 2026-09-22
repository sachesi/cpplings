#include "cpplings_test.hpp"

#include <cstddef>
#include <vector>

int copies = 0;

class Buffer {
public:
    explicit Buffer(std::size_t size) : data_(size) {}

    Buffer(const Buffer& other) : data_(other.data_) { ++copies; }

    Buffer& operator=(const Buffer& other) {
        data_ = other.data_;
        ++copies;
        return *this;
    }

    // TODO: Declaring a copy constructor stops the compiler from generating move
    // operations, so every `Buffer` is copied. Add a move constructor and a move
    // assignment operator.

    std::size_t size() const { return data_.size(); }

private:
    std::vector<int> data_;
};

TEST(buffers_are_moved_not_copied) {
    std::vector<Buffer> buffers;
    for (int i = 0; i < 10; ++i) {
        buffers.push_back(Buffer(1000));
    }
    CHECK_EQ(buffers.size(), 10);
    CHECK_EQ(copies, 0);
}
