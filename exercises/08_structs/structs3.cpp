// Structs contain data, but can also have logic. In this exercise, we've
// defined the `Package` struct, and we want to test some logic attached to it.

#include "cpplings_test.hpp"

#include <string>

struct Package {
    std::string sender_country;
    std::string recipient_country;
    int weight_in_grams = 0;

    // TODO: Fix the compiler error. The tests call this on a `const Package`.
    bool is_international() {
        // TODO: Return whether the package crosses a border.
    }

    int get_fees(int cents_per_gram) const {
        // TODO: Calculate the package's fees.
    }
};

TEST(create_international_package) {
    const Package package{"Spain", "Russia", 1200};
    CHECK(package.is_international());
}

TEST(create_local_package) {
    const Package package{"Canada", "Canada", 1200};
    CHECK(!package.is_international());
}

TEST(calculate_transport_fees) {
    const Package package{"Spain", "Spain", 1500};
    CHECK_EQ(package.get_fees(3), 4500);
}
