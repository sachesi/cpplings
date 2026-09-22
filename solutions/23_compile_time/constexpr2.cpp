#include <iostream>
#include <stdexcept>

// Reaching the `throw` while compiling is a compiler error.
consteval int port(int value) {
    if (value < 1 || value > 65535) {
        throw std::invalid_argument("port out of range");
    }
    return value;
}

const int http_port = port(80);
const int https_port = port(443);
const int admin_port = port(8080);

int main() {
    std::cout << "http: " << http_port << '\n';
    std::cout << "https: " << https_port << '\n';
    std::cout << "admin: " << admin_port << '\n';
}
