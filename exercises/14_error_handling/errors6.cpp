#include "cpplings_test.hpp"

#include <exception>
#include <stdexcept>
#include <string>

class InsufficientFunds : public std::runtime_error {
public:
    explicit InsufficientFunds(int missing)
        : std::runtime_error("insufficient funds: " + std::to_string(missing) + " missing"), missing_(missing) {}

    int missing() const { return missing_; }

private:
    int missing_;
};

void withdraw(int& balance, int amount) {
    if (amount > balance) {
        throw InsufficientFunds(amount - balance);
    }
    balance -= amount;
}

// Returns "ok" or the reason why the withdrawal failed.
// TODO: The test fails because the message is lost. Why? The compiler warns
// about it.
std::string try_withdraw(int& balance, int amount) {
    try {
        withdraw(balance, amount);
        return "ok";
    } catch (std::exception error) {
        return error.what();
    }
}

TEST(successful_withdrawal) {
    int balance = 50;
    CHECK_EQ(try_withdraw(balance, 30), "ok");
    CHECK_EQ(balance, 20);
}

TEST(failed_withdrawal) {
    int balance = 10;
    CHECK_EQ(try_withdraw(balance, 30), "insufficient funds: 20 missing");
    CHECK_EQ(balance, 10);
}
