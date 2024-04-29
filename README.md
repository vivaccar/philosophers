# PHILOSOPHERS

The Dining Philosophers problem is a classic synchronization problem in computer science, originally formulated by Edsger Dijkstra in 1965. It serves as an illustrative example of a problem in concurrent programming, where multiple processes or threads compete for shared resources while avoiding deadlock and starvation.
The objective of the Dining Philosophers problem is to design a solution that allows all philosophers to alternate between thinking, eating and sleeping without encountering deadlock or starvation. This solution must ensure that philosophers can only eat if they can acquire both chopsticks simultaneously, and must release the chopsticks when they are done eating to allow others to use them. Achieving this objective requires careful synchronization of access to shared resources, such as the chopsticks, to prevent conflicts and ensure fairness among the philosophers.

## Allowed functions

memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

## What are Threads?

In computer science, a thread is the smallest unit of execution within a process. Think of a process as a program running on your computer. Within that program, threads are individual paths of execution that can perform tasks concurrently.

## Key points about Threads

1. Concurrent Execution: Threads allow multiple tasks to be executed simultaneously within a single process. This concurrency enables programs to perform multiple operations concurrently, improving performance and responsiveness.

2. Lightweight: Threads are lightweight compared to processes. They share the same memory space and resources within a process, making thread creation and context switching faster and more efficient than creating and switching between processes.

3. Shared Resources: Threads within the same process share resources such as memory, files, and CPU time. This shared access requires careful synchronization to prevent conflicts and ensure data consistency.

4. Parallelism: Threads can run in parallel on multi-core processors, where each core executes a separate thread simultaneously. This parallel execution enables programs to leverage the full processing power of modern hardware for faster performance.

## What are Mutexes?

Mutex, short for mutual exclusion, is a synchronization primitive used to control access to shared resources by multiple threads or processes. Mutexes are essential for preventing race conditions and ensuring data integrity in concurrent programs.

## Key points about Mutexes

1. Exclusive Access: A mutex allows only one thread or process to access a shared resource at a time. It acts as a gatekeeper, ensuring that no two threads can access the resource simultaneously.

2. Locking and Unlocking: Mutexes provide two fundamental operations: locking and unlocking. When a thread wants to access a shared resource, it must first acquire the mutex lock. If the lock is available, the thread acquires it and proceeds to access the resource. After completing its task, the thread releases the mutex by unlocking it, allowing other threads to acquire the lock and access the resource.

3. Blocking and Waiting: If a thread attempts to acquire a mutex lock that is already held by another thread, it will be blocked or forced to wait until the lock becomes available. This blocking behavior ensures that threads do not execute concurrently when accessing critical sections of code or shared resources.

4. Critical Sections: Mutexes are commonly used to protect critical sections of code, where shared resources are accessed and modified. By enclosing critical sections with mutex locks, programmers can ensure that only one thread executes the code at a time, preventing race conditions and maintaining data consistency.
