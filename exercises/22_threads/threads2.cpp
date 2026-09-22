#include "cpplings_test.hpp"

#include <mutex>
#include <thread>
#include <vector>

struct Account {
    int balance = 0;
    // TODO: Several threads deposit money at the same time. Two threads can read
    // the same balance, and then one deposit overwrites the other. That's a data
    // race. Add a `std::mutex` to the account and lock it while the balance is
    // read and written.
};

void deposit(Account& account, int amount) {
    int current = account.balance;
    // Gives other threads a chance to run between reading and writing.
    std::this_thread::yield();
    account.balance = current + amount;
}

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
        // The jthreads are joined here, when the vector is destroyed.
    }

    CHECK_EQ(account.balance, 40'000);
}
