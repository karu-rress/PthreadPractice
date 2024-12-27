# PthreadPractice
Basic code with POSIX thread library.

## Part 1 - Basics of Pthread
- [basic.c](/Part1/basic.c) : Basic example of creating threads in C
- [ASSIGNMENT](/Part1/ASSIGNMENT.c): Write a program that decreases the execution time of the given code snippet, using thread.

## Part 2 - Race condition
- [1-race.c](/Part2/1-race.c) / [asm](/Part2/1-race.asm) : Race condition example
- [2-atomic.c](/Part2/2-atomic.c) / [asm](/Part2/2-atomic.asm) : Atomic operation using C11 _Atomic
- [3-mutex.c](/Part2/3-mutex.c) / [asm](/Part2/3-mutex.asm) : Mutex example
- [ASSIGNMENT](/Part2/ASSIGNMENT.c): Address the race condition using mutex, in the given code snippet.

## Part 3 - Advanced Pthread
- [1-deadlock.c](/Part3/1-deadlock.c) : Deadlock example
- [2-condition.c](/Part3/2-condition.c) : Implementing producer-consumer with condition variable
- ~~3-semaphore.c~~ : (Under construction)
- [4-dining-philosophers.c](/Part3/4-dining-philosophers.c) : Implementing dining philosophers problem
- ~~ASSIGNMENT~~ : (Under construction)
