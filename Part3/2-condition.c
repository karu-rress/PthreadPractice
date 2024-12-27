/**
 * 
 * @file: Part3/2-condition.c
 * 
 * @brief: Implementing producer-consumer with
 *         condition variables
 * 
 * Compile: gcc 2-condition.c -o 2-condition
 * Run: ./2-condition
 * 
 * @author: karu-rress
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>  // POSIX thread library
#include <unistd.h>   // POSIX OS API

#define MAX_ITER 30

// maybe smaller than MAX_ITER
int queue[MAX_ITER] = {0,};
int front = 0;
int back = -1;

pthread_mutex_t mutex;
pthread_cond_t cond;
 
void *producer(void *) {
    int temp;
    for (int i = 0; i < MAX_ITER; i++) {
        temp = rand() % 100; // call rand() outside of the mutex lock
        
        pthread_mutex_lock(&mutex);
        queue[++back] = temp;
        printf("Producer: random number %d generated.\n", queue[back]);
        
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void *consumer(void *) {
    int temp;
    for (int i = 0; i < MAX_ITER; i++) {
        pthread_mutex_lock(&mutex);
        if (back == -1) { // queue is empty
            printf("Consumer: waiting for producer...\n");
            
            // Before wait, unlock the mutex automatically
            pthread_cond_wait(&cond, &mutex);
            // After wait, lock the mutex automatically    
        }
        
        temp = queue[front++];
        if (front > back) {
            front = 0;
            back = -1;
        }
        printf("Consumer: got %d from the queue.\n", temp);
        
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}

int main() {
    pthread_t prod;
    pthread_t cons;

    pthread_mutex_init(&mutex, NULL); // initialize the mutex
    pthread_cond_init(&cond, NULL);   // initialize the CV

    pthread_create(&cons, NULL, consumer, NULL);
    sleep(1);
    pthread_create(&prod, NULL, producer, NULL);
    
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    return 0;
}