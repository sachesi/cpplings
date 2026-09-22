// This program spawns multiple threads that each compute a result. The main
// thread should collect all results once the threads are done.

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

    // TODO: Wait for every thread to finish before the results are used. A
    // `std::thread` that is still joinable when it's destroyed ends the program.

    for (int i = 0; i < 10; ++i) {
        if (results[i] != i * i + 1) {
            std::cout << "The result of thread " << i << " is missing!\n";
            return 1;
        }
        std::cout << "Thread " << i << " computed " << results[i] << '\n';
    }
}
