#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

int data[] = {45, 56, 78, 32, 9, 5};

// Thread function to calculate the sum of data
void* calculate_sum(void* arg) {
    int sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += data[i];
    }
    printf("Sum of data is %d\n", sum);
    pthread_exit(NULL);
}

// Thread function to find the maximum value in data
void* find_max(void* arg) {
    int max = data[0];
    for (int i = 1; i < 6; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    printf("Maximum value in data is %d\n", max);
    pthread_exit(NULL);
}

// Thread function to find the minimum value in data
void* find_min(void* arg) {
    int min = data[0];
    for (int i = 1; i < 6; i++) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    printf("Minimum value in data is %d\n", min);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads to perform different tasks
    pthread_create(&threads[0], NULL, calculate_sum, NULL);
    pthread_create(&threads[1], NULL, find_max, NULL);
    pthread_create(&threads[2], NULL, find_min, NULL);

    // Main thread waits for these threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
