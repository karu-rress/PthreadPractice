/**
 * 
 * @file: Part3/4-dining-philosophers.c
 * 
 * @brief: Implementing dining philosophers problem
 * 
 * Compile: gcc 4-dining-philosophers.c -o 4-dining-philosophers
 * Run: ./4-dining-philosophers
 * 
 * @author: karu-rress
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>  // POSIX thread library
#include <unistd.h>   // POSIX OS API
#include <signal.h>   // Signal function

#define NUM_PHILOSOPHERS 5

// Uncomment the line below to avoid deadlock
// #define USE_TRYLOCK

// Terminates the program
void deadlock_handler() {
    printf("===== Exiting the program =====\n");
    exit(-1);
}

pthread_mutex_t forks[NUM_PHILOSOPHERS];

struct philarg {
    int id;
    pthread_mutex_t *pleft;
    pthread_mutex_t *pright;
};

void *eat(void *arg) {
    struct philarg *parsed_arg = (struct philarg *)arg;
    int id = parsed_arg->id + 1;
    pthread_mutex_t *const pleft = parsed_arg->pleft;
    pthread_mutex_t *const pright = parsed_arg->pright;
    
    for (;;) {
        printf("Philosopher #%d is thinking.\n", id);
        sleep(1);
        
        pthread_mutex_lock(pleft); // pleft is already an address
        printf("Philosopher #%d picked up the left fork.\n", id);
        sleep(1);
        
#ifndef USE_TRYLOCK
        pthread_mutex_lock(pright);
#else
        // If the right fork is already being used,
        // release the left fork.
        if (pthread_mutex_trylock(pright) == 0) {
            pthread_mutex_unlock(pleft);
            printf("Philosopher #%d put down the left fork.\n", id);
            continue;
        }
#endif
        
        printf("Philosopher #%d picked up the right fork.\n", id);
        printf("Philosopher #%d is eating.\n", id);
        
        sleep(2);
        
        pthread_mutex_unlock(pright);
        printf("Philosopher #%d put down the right fork.\n", id);
        
        pthread_mutex_unlock(pleft);
        printf("Philosopher #%d put down the left fork.\n", id);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    struct philarg args[NUM_PHILOSOPHERS];
    
    // If the program doesn't complete in 15s,
    // force terminate.
    signal(SIGALRM, deadlock_handler);
    alarm(15);
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL); // initialize the fork(mutex)
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        args[i] = (struct philarg) {
            i, 
            &forks[i], 
            &forks[(i + 1) % NUM_PHILOSOPHERS]
        }; // Create argument using compound literals
            
        pthread_create(
            &philosophers[i], // pointer to the thread
            NULL,             // attributes
            eat,              // function
            (void *)&args[i]  // argument
        );
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    return 0;
}