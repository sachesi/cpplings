#include "cpplings_test.hpp"

#include <string>

class Logger {
public:
    explicit Logger(const std::string& prefix) : prefix_(prefix) {}

    std::string format(const std::string& message) const {
        return prefix_ + message;
    }

private:
    // TODO: A reference member refers to an object that the class doesn't own.
    // The logger outlives the string it refers to. Fix the class.
    const std::string& prefix_;
};

Logger make_logger() {
    std::string prefix = "[payment-service-eu-west] ";
    return Logger(prefix);
}

TEST(prefixes_messages) {
    Logger logger = make_logger();
    CHECK_EQ(logger.format("started"), "[payment-service-eu-west] started");
}
