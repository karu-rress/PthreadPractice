/**
 * 
 * @file: Part2/1-race.c
 * 
 * @brief: Race condition example
 * 
 * COMPILE TO ASSEMBLY FIRST
 * gcc 1-race.c -S -o 1-race.S
 * 
 * Compile: gcc 1-race.c -o race
 * Run: ./1-race
 * 
 * @author: karu-rress
 * 
 */

#include <stdio.h>

#include <pthread.h> // POSIX thread library
#include <unistd.h> // POSIX OS API

// NOTE: you may want to use 'volatile' to prevent optimization
int counter = 0;

// No input, no output
void *add(void *) {
    for (int i = 0; i < 1000000; i++) {
        // Critical section
        // The addition operation is not atomic
        // 1. Read the value of counter
        // 2. Add 1 to the value
        // 3. Write the new value back to counter
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