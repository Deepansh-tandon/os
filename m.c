#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_CLIENTS 5

// Array representing accounts with initial balances
int accounts[9] = {550, 450, 300, 700, 500, 600, 400, 800, 350};

// Mutex lock to ensure thread safety
pthread_mutex_t lock;

// Function for deposit
void* Deposit(void* arg) {
    int client_id = *(int*)arg; // Get client ID
    int amount;
    int account_index = rand() % 9; // Random account selection

    printf("\nClient %d: Enter amount to deposit: ", client_id);
    scanf("%d", &amount);

    pthread_mutex_lock(&lock); // Lock for critical section
    accounts[account_index] += amount;
    printf("Client %d deposited %d into account %d. New balance: %d\n",
           client_id, amount, account_index, accounts[account_index]);
    pthread_mutex_unlock(&lock); // Unlock after critical section

    pthread_exit(NULL);
}

// Function for withdrawal
void* Withdraw(void* arg) {
    int client_id = *(int*)arg; // Get client ID
    int amount;
    int account_index = rand() % 9; // Random account selection

    printf("\nClient %d: Enter amount to withdraw: ", client_id);
    scanf("%d", &amount);

    pthread_mutex_lock(&lock); // Lock for critical section
    if (accounts[account_index] >= amount) {
        accounts[account_index] -= amount;
        printf("Client %d withdrew %d from account %d. New balance: %d\n",
               client_id, amount, account_index, accounts[account_index]);
    } else {
        printf("Client %d: Insufficient funds in account %d. Balance: %d\n",
               client_id, account_index, accounts[account_index]);
    }
    pthread_mutex_unlock(&lock); // Unlock after critical section

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_CLIENTS];
    int client_ids[NUM_CLIENTS];
    int i;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Assign client IDs
    for (i = 0; i < NUM_CLIENTS; i++) {
        client_ids[i] = i + 1; // Client IDs start from 1
    }

    // Create threads for deposit and withdrawal
    for (i = 0; i < NUM_CLIENTS; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, Deposit, &client_ids[i]);
        } else {
            pthread_create(&threads[i], NULL, Withdraw, &client_ids[i]);
        }
    }

    // Wait for all threads to complete
    for (i = 0; i < NUM_CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("\nAll transactions completed.\n");
    return 0;
}
