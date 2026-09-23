#include "cpplings_test.hpp"

#include <memory>
#include <string>
#include <vector>

class Licensed {
public:
    virtual ~Licensed() = default;

    // A virtual function with a default implementation.
    virtual std::string licensing_info() const {
        return "Default license";
    }
};

class SomeSoftware : public Licensed {};

class OtherSoftware : public Licensed {
public:
    std::string licensing_info() const override {
        return "MIT license";
    }
};

std::string describe(const Licensed& software) {
    return software.licensing_info();
}

TEST(default_license) {
    SomeSoftware software;
    CHECK_EQ(describe(software), "Default license");
}

TEST(own_license) {
    OtherSoftware software;
    CHECK_EQ(describe(software), "MIT license");
}

TEST(mixed_collection) {
    std::vector<std::unique_ptr<Licensed>> programs;
    programs.push_back(std::make_unique<SomeSoftware>());
    programs.push_back(std::make_unique<OtherSoftware>());
    CHECK_EQ(programs[0]->licensing_info(), "Default license");
    CHECK_EQ(programs[1]->licensing_info(), "MIT license");
}
