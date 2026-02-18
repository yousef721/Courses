#include <stdio.h>      // Provides printf()
#include <unistd.h>     // Provides getpid()
#include <pthread.h>    // Provides POSIX threads API
#include <stdlib.h>     // Provides atoi() for converting string to integer

// Global variables shared between threads
unsigned long s = 0;  // To store sum
unsigned long m = 1;  // To store product

// Thread function to calculate sum from 1 to p
void *runner1(void *param){
    unsigned long p;

    // Convert the parameter from char* (string) to integer
    // argv[] values are strings, so atoi() converts to int
    p = atoi((char*)param);

    // Compute sum of numbers from 1 to p
    for(unsigned long i = 1; i <= p; i++)
        s += i;  // Add i to global sum

    // Exit the thread
    pthread_exit(0);
}

// Thread function to calculate product (factorial) from 1 to x
void *runner2(void *param){
    unsigned long x;

    // Convert the parameter from char* to integer
    x = atoi((char*)param);

    // Compute product of numbers from 1 to x
    for(unsigned long i = 1; i <= x; i++)
        m *= i;  // Multiply i to global product

    // Exit the thread
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    // pthread_t variables to hold thread IDs
    pthread_t tid1, tid2;
    pthread_attr_t attr;  // Thread attributes object

    // Initialize thread attributes with default values
    pthread_attr_init(&attr);

    // Create two threads:
    // Thread 1 calculates sum, takes argv[1] as argument
    pthread_create(&tid1, &attr, runner1, argv[1]);

    // Thread 2 calculates product, takes argv[2] as argument
    pthread_create(&tid2, &attr, runner2, argv[2]);

    // Wait for both threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Print the results
    printf("\nSum = %lu\n", s);
    printf("Product = %lu\n", m);

    // Indicate main thread has finished
    printf("\nMain Thread Done, PID = %d\n", getpid());
}
