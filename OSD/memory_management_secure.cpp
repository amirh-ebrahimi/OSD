#include <iostream>
#include <vector>
#include <queue>
#include <mutex>

class MemoryPool {
public:
    MemoryPool(size_t sizeOfEachBlock, size_t numberOfBlocks) {
        for(size_t i = 0; i < numberOfBlocks; ++i) {
            free_blocks.push(new char[sizeOfEachBlock]);
        }
    }

    ~MemoryPool() {
        std::lock_guard<std::mutex> lock(mtx);  // lock while cleaning up
        while(!free_blocks.empty()) {
            delete[] free_blocks.front();
            free_blocks.pop();
        }
    }

    void* allocate() {
        std::lock_guard<std::mutex> lock(mtx);  // lock while allocating

        if(free_blocks.empty()) {
            throw std::bad_alloc();
        }

        void* block = free_blocks.front();
        free_blocks.pop();
        return block;
    }

    void deallocate(void* block) {
        std::lock_guard<std::mutex> lock(mtx);  // lock while deallocating
        free_blocks.push((char*)block);
    }

private:
    std::queue<char*> free_blocks;
    std::mutex mtx;  // mutex for thread safety
};

int main() {
    MemoryPool pool(sizeof(int), 10);  // allocate memory for 10 integers

    int* a1 = (int*)pool.allocate();   // allocate memory for an integer
    *a1 = 10;
    std::cout << *a1 << std::endl;     // prints: 10

    int* a2 = (int*)pool.allocate();   // allocate memory for another integer
    *a2 = 20;
    std::cout << *a2 << std::endl;     // prints: 20

    pool.deallocate(a1);               // deallocate memory for a1
    pool.deallocate(a2);               // deallocate memory for a2

    return 0;
}
