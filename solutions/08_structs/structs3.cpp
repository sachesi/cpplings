#include "cpplings_test.hpp"

#include <string>

struct Package {
    std::string sender_country;
    std::string recipient_country;
    int weight_in_grams = 0;

    bool is_international() const {
        return sender_country != recipient_country;
    }

    int get_fees(int cents_per_gram) const {
        return cents_per_gram * weight_in_grams;
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
