#include "cpplings_test.hpp"

#include <string>
#include <utility>

class Logger {
public:
    explicit Logger(std::string prefix) : prefix_(std::move(prefix)) {}

    std::string format(const std::string& message) const {
        return prefix_ + message;
    }

private:
    // The logger keeps its own copy.
    std::string prefix_;
};

Logger make_logger() {
    std::string prefix = "[payment-service-eu-west] ";
    return Logger(prefix);
}

TEST(prefixes_messages) {
    Logger logger = make_logger();
    CHECK_EQ(logger.format("started"), "[payment-service-eu-west] started");
}
