#include <iostream>
#include <fcntl.h>       /* For O_* constants */
#include <sys/stat.h>    /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>

int main() {
    const char* memname = "sample";
    const size_t region_size = sysconf(_SC_PAGE_SIZE);

    int fd = shm_open(memname, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1) {
        std::cerr << "Shared memory failed\n";
        return 1;
    }

    if (ftruncate(fd, region_size) != 0) {
        std::cerr << "Truncation failed\n";
        return 1;
    }

    void* ptr = mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Map failed\n";
        return 1;
    }

    close(fd);

    sem_t* sema = sem_open("sema", O_CREAT, 0666, 0);
    
    char* msg = (char*)ptr;
    while(true) {
        std::cout << "Enter a message: ";
        std::cin.getline(msg, region_size);
        sem_post(sema);
    }

    return 0;
}
