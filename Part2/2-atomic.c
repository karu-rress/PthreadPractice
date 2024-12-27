/**
 * 
 * @file: Part2/2-atomic.c
 * 
 * @brief: Atomic operation using C11 _Atomic
 * 
 * COMPILE TO ASSEMBLY FIRST
 * gcc 2-atomic.c -S -o 2-atomic.S
 * 
 * Compile: gcc 2-atomic.c -o race
 * Run: ./2-atomic
 * 
 * @author: karu-rress
 * 
 */

#include <stdio.h>

#include <pthread.h> // POSIX thread library
#include <unistd.h> // POSIX OS API

_Atomic int counter = 0;

// No input, no output
void *add(void *) {
    for (int i = 0; i < 1000000; i++) {
        // Critical section
        // This is an atomic operation!
        counter += 1;
    }

    return NULL;
}

int main() {
    pthread_t thread[2]; // Create 2 threads

    for (int i = 0; i < 2; i++) {
        pthread_create(&thread[i], NULL, add, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("Counter: %d\n", counter);

    return 0;
}
