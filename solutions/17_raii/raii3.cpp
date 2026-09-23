#include "cpplings_test.hpp"

#include <future>
#include <mutex>
#include <stdexcept>

std::mutex account_mutex;
int balance = 100;

void withdraw(int amount) {
    // Unlocks in its destructor, however the function is left.
    std::lock_guard lock(account_mutex);
    if (amount > balance) {
        throw std::runtime_error("insufficient funds");
    }
    balance -= amount;
}

bool mutex_is_free() {
    return std::async(std::launch::async, [] {
               if (account_mutex.try_lock()) {
                   account_mutex.unlock();
                   return true;
               }
               return false;
           })
        .get();
}

TEST(successful_withdrawal) {
    withdraw(30);
    CHECK_EQ(balance, 70);
    CHECK(mutex_is_free());
}

TEST(failed_withdrawal_releases_the_mutex) {
    CHECK_THROWS(withdraw(500));
    CHECK(mutex_is_free());
}
