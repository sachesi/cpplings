#include <iostream>
#include <string_view>

namespace delicious_snacks {
namespace fruits {
constexpr std::string_view PEAR = "Pear";
constexpr std::string_view APPLE = "Apple";
} // namespace fruits

namespace veggies {
constexpr std::string_view CUCUMBER = "Cucumber";
constexpr std::string_view CARROT = "Carrot";
} // namespace veggies
} // namespace delicious_snacks

namespace fruit = delicious_snacks::fruits;
namespace veggie = delicious_snacks::veggies;
using delicious_snacks::veggies::CARROT;

int main() {
    std::cout << "favorite snacks: " << fruit::PEAR << " and " << veggie::CUCUMBER << '\n';
    std::cout << "also nice: " << CARROT << " and " << fruit::APPLE << '\n';
}
