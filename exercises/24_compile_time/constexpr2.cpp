#include <iostream>
#include <stdexcept>

// Validates a port number.
// TODO: The program crashes when it starts because one of the ports below is
// invalid. It would be better to find such mistakes while compiling. Mark the
// function `consteval` so that it can only run at compile time, then fix the
// mistake that the compiler finds.
constexpr int port(int value) {
    if (value < 1 || value > 65535) {
        throw std::invalid_argument("port out of range");
    }
    return value;
}

const int http_port = port(80);
const int https_port = port(443);
const int admin_port = port(80800);

int main() {
    std::cout << "http: " << http_port << '\n';
    std::cout << "https: " << https_port << '\n';
    std::cout << "admin: " << admin_port << '\n';
}
