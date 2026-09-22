#include "cpplings_test.hpp"

#include <cstddef>
#include <utility>
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

    // `noexcept` matters: when the vector grows, it only moves its elements if
    // moving can't throw. Otherwise it copies them.
    Buffer(Buffer&& other) noexcept : data_(std::move(other.data_)) {}

    Buffer& operator=(Buffer&& other) noexcept {
        data_ = std::move(other.data_);
        return *this;
    }

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
