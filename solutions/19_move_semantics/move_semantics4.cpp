#include "cpplings_test.hpp"

#include <memory>
#include <string>
#include <utility>

int copies = 0;

struct Payload {
    std::string data;

    explicit Payload(std::string d) : data(std::move(d)) {}
    Payload(const Payload& other) : data(other.data) { ++copies; }
    Payload(Payload&& other) noexcept : data(std::move(other.data)) {}
};

struct Message {
    Payload payload;

    explicit Message(Payload p) : payload(std::move(p)) {}
};

// `Arg&&` in a template is a forwarding reference: it binds to lvalues and
// rvalues. `std::forward` moves only if the caller passed an rvalue.
template <typename T, typename Arg>
std::unique_ptr<T> make(Arg&& arg) {
    return std::unique_ptr<T>(new T(std::forward<Arg>(arg)));
}

TEST(temporaries_are_moved) {
    copies = 0;
    auto message = make<Message>(Payload("hello"));
    CHECK_EQ(message->payload.data, "hello");
    CHECK_EQ(copies, 0);
}

TEST(named_objects_are_copied) {
    copies = 0;
    Payload payload("world");
    auto message = make<Message>(payload);
    CHECK_EQ(message->payload.data, "world");
    CHECK_EQ(payload.data, "world");
    CHECK_EQ(copies, 1);
}
