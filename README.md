# C++ Operating System Concepts Demonstrations

This repository contains C++ implementations of various low-level operating system concepts, including process management, memory management, inter-process communication (IPC), and thread synchronization.

## Process Management

The process management example is a simple demonstration of creating a child process using `fork()` and executing a new program in the child process with `exec()`. 

To run the code:

```shell
$ g++ process_management.cpp -o process_management
$ ./process_management
```

## Memory Management

The memory management example provides a simple memory pool implementation using C++. It allows for allocation and deallocation of memory blocks from a predefined pool.

This implementation ensures thread safety by utilizing std::mutex to protect the critical sections of the code.

To run the code:
```shell
$ g++ memory_management.cpp -o memory_management
$ ./memory_management
```

## Inter-Process Communication

The inter-process communication example involves two separate programs (```writer.cpp ``` and ```reader.cpp ```) that communicate through shared memory in a POSIX environment. A semaphore is used for synchronization.

Compile and run the writer program:

```shell
$ g++ writer.cpp -o writer
$ ./writer
```
In another terminal, compile and run the reader program:

```shell
$ g++ reader.cpp -o reader
$ ./reader
```

## Thread Synchronization

The thread synchronization example demonstrates a producer-consumer scenario. The producer adds numbers to a queue and the consumer removes them, with the operations properly synchronized.

To run the code:

```shell
$ g++ thread_sync.cpp -o thread_sync
$ ./thread_sync
```

## Dependencies

These examples require a modern C++ compiler and the Boost.Asio library for the IPC example. Ensure that you have these installed and correctly set up before compiling and running the examples
