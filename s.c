#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


int VAR = 10;  // Shared variable
sem_t sem;  // Semaphore for synchronization

// Child process function
void child_process() {
    printf("Child Process: Initial VAR = %d\n", VAR);
    VAR -= 2;  // Decrement VAR by 2
    printf("Child Process: VAR after decrement = %d\n", VAR);
    sem_post(&sem);  // Signal parent that child is done
    exit(0);  // Exit child process
}

// Parent process function
void parent_process() {
    sem_wait(&sem);  // Wait for child to finish
    printf("Parent Process: Initial VAR = %d\n", VAR);
    VAR += 2;  // Increment VAR by 2
    printf("Parent Process: VAR after increment = %d\n", VAR);
}

int main() {
    sem_init(&sem, 0, 0);  // Initialize semaphore with 0 (child goes first)
    pid_t pid = fork();  // Create a child process

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        child_process();
    } else {
        // Parent process
        parent_process();
        wait(NULL);  // Wait for child to finish
    }

    sem_destroy(&sem);  // Clean up semaphore
    return 0;
}
