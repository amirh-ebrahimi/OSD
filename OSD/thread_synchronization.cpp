#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> produced_nums;
std::mutex mtx;
std::condition_variable cv;

void producer(int n) {
    for (int i = 0; i < n; ++i) {
        {
            // lock the mutex before accessing the shared queue
            std::unique_lock<std::mutex> lock(mtx);
            produced_nums.push(i);
            std::cout << "Producing " << i << std::endl;
        } // unlock the mutex
        // notify the condition variable to wake up the consumer thread
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (produced_nums.empty()) {
            // block current thread until the condition variable is notified
            cv.wait(lock);
        }
        std::cout << "Consuming " << produced_nums.front() << std::endl;
        produced_nums.pop();
    }
}

int main() {
    // create producer and consumer threads
    std::thread prod(producer, 10);
    std::thread cons(consumer);

    // join the threads
    prod.join();
    cons.detach();
}
