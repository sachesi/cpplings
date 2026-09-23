#include "cpplings_test.hpp"

#include <future>
#include <mutex>
#include <stdexcept>

std::mutex account_mutex;
int balance = 100;

void withdraw(int amount) {
    // TODO: If an exception is thrown, `unlock` is never called and the mutex
    // stays locked forever. Use `std::lock_guard` to lock the mutex instead.
    account_mutex.lock();
    if (amount > balance) {
        throw std::runtime_error("insufficient funds");
    }
    balance -= amount;
    account_mutex.unlock();
}

// Checks from another thread whether the mutex can be locked.
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
