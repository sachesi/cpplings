#include <iostream>
#include <string_view>

namespace sausage_factory {

std::string_view get_secret_recipe() {
    return "Ginger";
}

void make_sausage() {
    std::cout << "sausage with " << get_secret_recipe() << "!\n";
}

} // namespace sausage_factory

int main() {
    // TODO: Fix the compiler error.
    make_sausage();
}
