/**
 * 
 * @file: Part3/5-sequential.c
 * 
 * @brief: Sequential execution with zero semaphores
 * 
 * Compile: gcc 5-sequential.c -o 5-sequential
 * Run: ./5-sequential
 * 
 * @author: karu-rress
 * 
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>    // POSIX thread library
#include <unistd.h>     // POSIX OS API
#include <semaphore.h>  // Semaphores

// Semaphore variables
sem_t s1;
sem_t s2;

// Work1 should start first
void *work1(void *) {
    printf("Work 1 started.\n");
    sleep(1);
    printf("Work 1 finished. Starting Work 2...\n");
    sem_post(&s1);
}

// Work2 should start after work1
void *work2(void *) {
    // Wait for work1 to be finished
    sem_wait(&s1);
    printf("Work 2 started.\n");
    sleep(1);
    printf("Work 2 finished. Starting Work 3...\n");
    sem_post(&s2);
}

// Work3 should start after work2
void *work3(void *) {
    // Wait for work2 to be finished
    sem_wait(&s2);
    printf("Work 3 started.\n");
    sleep(1);
    printf("Work 3 finished.\n");
}

int main() {
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    
    // Run threads in reversed order
    pthread_create(&thread3, NULL, work3, NULL);
    sleep(1);
    pthread_create(&thread2, NULL, work2, NULL);
    sleep(1);
    pthread_create(&thread1, NULL, work1, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
}
