// A producer thread puts jobs into a queue, and a consumer thread processes them.

#include "cpplings_test.hpp"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

std::mutex queue_mutex;
std::condition_variable queue_changed;
std::queue<int> jobs;
bool producer_done = false;

void produce() {
    for (int job = 1; job <= 5; ++job) {
        {
            std::lock_guard lock(queue_mutex);
            jobs.push(job);
        }
        queue_changed.notify_one();
    }
    {
        std::lock_guard lock(queue_mutex);
        producer_done = true;
    }
    queue_changed.notify_one();
}

int consume() {
    int sum = 0;
    while (true) {
        std::unique_lock lock(queue_mutex);
        // TODO: A notification only wakes up threads that are waiting at that
        // moment. If the producer is faster than the consumer, the consumer waits
        // forever. Also, `wait` may wake up without a notification. Wait until
        // there is a job or the producer is done. The program is stopped after 10
        // seconds.
        queue_changed.wait(lock);

        if (jobs.empty() && producer_done) {
            return sum;
        }
        sum += jobs.front();
        jobs.pop();
    }
}

TEST(all_jobs_are_processed) {
    std::jthread producer(produce);
    // Makes sure that the producer is done before the consumer starts.
    producer.join();

    int sum = 0;
    std::jthread consumer([&sum] { sum = consume(); });
    consumer.join();

    CHECK_EQ(sum, 1 + 2 + 3 + 4 + 5);
}
