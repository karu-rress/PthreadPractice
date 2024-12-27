/**
 * 
 * @file: Part1/basic.c
 * 
 * @brief: Basic example of creating threads in C
 * 
 * Compile: gcc basic.c -o basic
 * Run: ./basic
 * 
 * @author: karu-rress
 * 
 */

#include <stdio.h>

#include <pthread.h> // POSIX thread library
#include <unistd.h> // POSIX OS API
#include <sys/syscall.h> // Linux-specific system call

// Function to be executed by the thread
// must return void pointer and accept void pointer as argument
void *func(void *arg) {
    int tid = syscall(SYS_gettid); // Get thread ID

    for (int i = 0; i < 5; i++) {
        printf("[%d] Hello, I'm thread %s (tid=%d)\n",
            i + 1, (char *)arg, tid);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thread[3]; // Create 3 threads
    const char *names[] = {"A", "B", "C"};

    for (int i = 0; i < 3; i++) {
        // Create a new thread
        // 1st argument: pointer to the thread to initialize
        // 2nd argument: thread attributes (NULL for default)
        // 3rd argument: function to be executed by the thread
        // 4th argument: argument to be passed to the function
        pthread_create(&thread[i], NULL, func, (void *)names[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        // Q. what if we don't <<join>> the threads?
        //    Comment out the following line and see what happens.
        pthread_join(thread[i], NULL);
    }

    return 0;
}