#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::vector<int> results(10);
    std::vector<std::thread> handles;

    for (int i = 0; i < 10; ++i) {
        handles.emplace_back([i, &results] {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            results[i] = i * i + 1;
        });
    }

    // `join` blocks until the thread is finished. Afterwards, everything the
    // thread wrote is visible to this thread.
    for (std::thread& handle : handles) {
        handle.join();
    }

    for (int i = 0; i < 10; ++i) {
        if (results[i] != i * i + 1) {
            std::cout << "The result of thread " << i << " is missing!\n";
            return 1;
        }
        std::cout << "Thread " << i << " computed " << results[i] << '\n';
    }
}
