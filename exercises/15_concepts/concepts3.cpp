#include "cpplings_test.hpp"

#include <memory>
#include <string>
#include <vector>

class Licensed {
public:
    virtual ~Licensed() = default;

    // TODO: Derived classes may provide their own licensing info, but calling the
    // function through a `Licensed&` always runs this version. Make the call use
    // the version of the actual object.
    std::string licensing_info() const {
        return "Default license";
    }
};

class SomeSoftware : public Licensed {};

class OtherSoftware : public Licensed {
public:
    // TODO: Mark this function with `override` once the base function allows it.
    std::string licensing_info() const {
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
