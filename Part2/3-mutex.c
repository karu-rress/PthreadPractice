/**
 * 
 * @file: Part2/3-mutex.c
 * 
 * @brief: Race condition example
 * 
 * COMPILE TO ASSEMBLY FIRST
 * gcc 3-mutex.c -S -o 3-mutex.S
 * 
 * Compile: gcc 3-mutex.c -o race
 * Run: ./3-mutex
 * 
 * @author: karu-rress
 * 
 */

#include <stdio.h>

#include <pthread.h> // POSIX thread library
#include <unistd.h> // POSIX OS API

int counter = 0;

// You may init the mutex with PTHREAD_MUTEX_INITIALIZER,
// but that's an older way of doing it
pthread_mutex_t mutex;

// No input, no output
void *add(void * _) {
    for (int i = 0; i < 1000000; i++) {
        // Critical section
        pthread_mutex_lock(&mutex); // Lock the mutex
        counter += 1;
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }

    return NULL;
}

int main() {
    pthread_t thread[2]; // Create 2 threads

    pthread_mutex_init(&mutex, NULL); // initialize the mutex

    for (int i = 0; i < 2; i++) {
        pthread_create(&thread[i], NULL, add, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("Counter: %d\n", counter);

    return 0;
}