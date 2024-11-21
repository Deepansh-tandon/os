// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>

// sem_t semaphore;  // Semaphore for mutual exclusion
// int shared_var = 0;  // Shared variable to be updated by threads

// // Thread 1 function to update the shared variable
// void* thread1_func(void* arg) {
//     // Wait (enter critical section)
//     sem_wait(&semaphore);
    
//     // Critical section
//     shared_var += 5;  // Update the shared variable
//     printf("Thread 1 updated shared_var to %d\n", shared_var);
    
//     // Signal (leave critical section)
//     sem_post(&semaphore);
    
//     pthread_exit(NULL);
// }

// // Thread 2 function to update the shared variable
// void* thread2_func(void* arg) {
//     // Wait (enter critical section)
//     sem_wait(&semaphore);
    
//     // Critical section
//     shared_var += 10;  // Update the shared variable
//     printf("Thread 2 updated shared_var to %d\n", shared_var);
    
//     // Signal (leave critical section)
//     sem_post(&semaphore);
    
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread1, thread2;

//     // Initialize the semaphore with value 1 (binary semaphore)
//     sem_init(&semaphore, 0, 1);

//     // Create threads
//     pthread_create(&thread1, NULL, thread1_func, NULL);
//     pthread_create(&thread2, NULL, thread2_func, NULL);

//     // Wait for threads to finish
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     // Destroy the semaphore
//     sem_destroy(&semaphore);

//     printf("Final value of shared_var: %d\n", shared_var);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0;              // Index for the producer
int out = 0;             // Index for the consumer

// Semaphores
sem_t empty;  // Counts the empty slots in the buffer
sem_t full;   // Counts the filled slots in the buffer
pthread_mutex_t mutex;  // Protects access to the buffer

// Producer function
void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Produces 10 items
        item = rand() % 100;  // Generate a random item

        // Wait for an empty slot
        sem_wait(&empty);

        // Lock the buffer to add the item
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;  // Move to the next slot
        pthread_mutex_unlock(&mutex);

        // Signal that a new item is available
        sem_post(&full);

        sleep(1);  // Simulate production time
    }
    pthread_exit(NULL);
}

// Consumer function
void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Consumes 10 items
        // Wait for an available item
        sem_wait(&full);

        // Lock the buffer to remove the item
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  // Move to the next slot
        pthread_mutex_unlock(&mutex);

        // Signal that a slot is now empty
        sem_post(&empty);

        sleep(1);  // Simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // BUFFER_SIZE empty slots
    sem_init(&full, 0, 0);             // 0 full slots initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
