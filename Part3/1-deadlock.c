/**
 * 
 * @file: Part3/1-deadlock.c
 * 
 * @brief: Deadlock example
 * 
 * Compile: gcc 1-deadlock.c -o 1-deadlock
 * Run: ./1-deadlock
 * 
 * @author: karu-rress
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>  // POSIX thread library
#include <unistd.h>   // POSIX OS API
#include <signal.h>   // Signal function
 
// Terminates the program if deadlock occurs
void deadlock_handler() {
    printf("Deadlock detected! Exiting...\n");
    exit(-1);
}

// You may init the mutex with PTHREAD_MUTEX_INITIALIZER,
// but that's an older way of doing it
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
 
void *work1(void *) {
    printf("Thread 1: Attemping to acquire mutex1.\n");
    pthread_mutex_lock(&mutex1); // Lock the mutex 1
    
    printf("Thread 1: Acquired mutex1.\n");
    sleep(1); // Sleep for 1 second
    
    printf("Thread 1: Attempting to acquire mutex2.\n");
    pthread_mutex_lock(&mutex2); // Lock the mutex 2
    
    printf("Thread 1: Acquired mutex2.\n");

    // Unlock the mutexes    
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
}

void *work2(void *) {
    printf("Thread 2: Attemping to acquire mutex2.\n");
    pthread_mutex_lock(&mutex2); // Lock the mutex 2
    
    printf("Thread 2: Acquired mutex2.\n");
    sleep(1); // Sleep for 1 second
    
    printf("Thread 2: Attempting to acquire mutex1.\n");
    pthread_mutex_lock(&mutex1); // Lock the mutex 1
    
    printf("Thread 2: Acquired mutex1.\n");

    // Unlock the mutexes    
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
}


int main() {
    pthread_t thread1;
    pthread_t thread2;
    
    // If the program doesn't complete in 10s,
    // assume that deadlock has occured.
    signal(SIGALRM, deadlock_handler);
    alarm(10);

    pthread_mutex_init(&mutex1, NULL); // initialize the mutex1
    pthread_mutex_init(&mutex2, NULL); // initialize the mutex2

    pthread_create(&thread1, NULL, work1, NULL);
    pthread_create(&thread2, NULL, work2, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("The program has finished successfully.\n");
    
    return 0;
}