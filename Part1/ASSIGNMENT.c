/**
 *
 * ASSIGNMENT OF PART 1
 *
 * Write a program that decreases the execution time
 * of the given code snippet, using thread.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>

#define SIZE 10000
#define MOD 10001

// DO NOT MODIFY THIS FUNCTION
long long get(int i, long long *array) {
    long long t = array[i];
    for (int i = 0; i < 10; i++) {
        t = t * 3 + 298413201;
        t %= MOD;
    }
    return t * array[i];
}

// DO NOT MODIFY THIS FUNCTION
long long action(long long sum, int i, long long *array) {
    for (int i = 0; i < SIZE; i++) {
        sum += get(i, array) * (i + 50001) * get(i, array) + get(i, array);
        sum %= MOD;
    }
    return sum;
}

int main() {
    FILE *fp;
    long long *array;
    
    // Dynamically allocate memory for the array
    array = (long long *)calloc(SIZE, sizeof(long long));

    // Open the file in read mode
    fp = fopen("data.bin", "rb");

    // Read the file into the array
    for (int i = 0; i < SIZE; i++) {
        unsigned char a;
        fread(&a, sizeof a, 1, fp);
        array[i] = (long long)a;
    }

    clock_t start = clock();

    volatile long long sum = 0;
    
////////////// YOUR CODE GOES HERE //////////////


    // TODO: Create a thread to calculate the sum of the array.
    // Create as many threads as you want.
    // Your code should follow this logic:
    //   from 0 to SIZE, do action() for each element
    for (int i = 0; i < SIZE; i++) {
        sum = action(sum, i, array);
    }
    


////////////////////////////////////////////////

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time: %f\n", time_spent);
    printf("Result: %lld\n", sum);

    fclose(fp);
    free(array);

    return 0;
}
