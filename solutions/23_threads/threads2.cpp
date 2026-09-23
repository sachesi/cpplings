#include "cpplings_test.hpp"

#include <mutex>
#include <thread>
#include <vector>

struct Account {
    int balance = 0;
    std::mutex mutex;
};

void deposit(Account& account, int amount) {
    // Only one thread at a time gets past this line until `lock` is destroyed.
    std::lock_guard lock(account.mutex);
    int current = account.balance;
    std::this_thread::yield();
    account.balance = current + amount;
}

// For a single counter, `std::atomic<int>` with `fetch_add` (or `+=`) is a
// lighter alternative to a mutex.

TEST(deposits_from_many_threads) {
    Account account;

    {
        std::vector<std::jthread> threads;
        for (int t = 0; t < 4; ++t) {
            threads.emplace_back([&account] {
                for (int i = 0; i < 10'000; ++i) {
                    deposit(account, 1);
                }
            });
        }
    }

    CHECK_EQ(account.balance, 40'000);
}
