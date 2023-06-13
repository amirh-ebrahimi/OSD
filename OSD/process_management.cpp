#include <iostream>
#include <thread>
#include <vector>

void hello() {
    std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    // Create a vector of std::thread objects
    std::vector<std::thread> threads;

    // Spawn 5 threads
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(hello));
    }

    // Join the threads to the main thread
    for(auto& thread : threads){
        thread.join();
    }

    return 0;
}
