#include <stdio.h>      // Provides printf() function
#include <unistd.h>     // Provides getpid() function
#include <pthread.h>    // Provides POSIX threads API

// Function executed by each thread
void *runner1(void *param)
{
    int *p;                 // Pointer to an integer

    // Cast the void* argument to int* because we are passing address of an int
    p = (int *)(param);

    // Print the value pointed to by p (i.e., the integer value)
    printf("\nValue = %d\n", *p);

    // Terminate the thread normally
    pthread_exit(0);
}

int main()
{
    pthread_t tid[20];      // Array to store 20 thread IDs
    int arr[20];            // Array of 20 integers to pass to threads

    // Initialize the array with values 10, 20, 30, ..., 200
    for(int i = 0; i < 20; i++)
        arr[i] = (i + 1) * 10;

    pthread_attr_t attr;    // Thread attributes object

    // Initialize thread attributes with default values
    pthread_attr_init(&attr);

    // Create 20 threads
    for(int i = 0; i < 20; i++)
        // Each thread executes runner1() function
        // &arr[i] is passed so each thread gets its unique integer value
        pthread_create(&tid[i], &attr, runner1, &arr[i]);

    // Wait for all 20 threads to complete
    for(int i = 0; i < 20; i++)
        pthread_join(tid[i], NULL);

    // This executes only after all threads finish
    printf("\nMain Thread Done, PID = %d\n", getpid());
}
