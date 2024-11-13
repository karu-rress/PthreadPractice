/**
 *
 * ASSIGNMENT OF PART 2
 *
 * Address the race condition using mutex,
 * in the given code snippet.
 *
 */

#include <stdio.h>

#include <pthread.h>
#include <unistd.h>

volatile int counter1 = 0;
volatile int counter2 = 0;

void *add1(void * _) {
    for (int i = 0; i < 10000000; i++) {
        counter1 += 1;
    }

    return NULL;
}

void *add2(void * _) {
    for (int i = 0; i < 10000000; i++) {
        counter2 += 1;
    }

    return NULL;
}



int main() {
    pthread_t thread[5];

    // initialize threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&thread[i], NULL, add1, NULL);
    }
    for (int i = 2; i < 5; i++) {
        pthread_create(&thread[i], NULL, add2, NULL);
    }

    // join threads
    for (int i = 0; i < 5; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("Counter1: %d\n", counter1);
    printf("Counter2: %d\n", counter2);

    return 0;
}