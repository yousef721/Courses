#include <stdio.h>      // Provides printf()
#include <unistd.h>     // Provides getpid()
#include <pthread.h>    // Provides POSIX threads API

unsigned long sum = 0;  // Global variable shared between threads

// Thread function
void *runner1(void *param){
    // Loop from 0 to 999,999 and accumulate sum
    for(unsigned long i = 0; i < 1000000; i++)
        sum += i;  // Increment global variable

    // Exit the thread normally
    pthread_exit(0);
}

int main()
{
    pthread_t tid;           // Thread ID
    pthread_attr_t attr;     // Thread attribute object

    // Initialize thread attributes with default values
    pthread_attr_init(&attr);

    // Create a thread running runner1
    pthread_create(&tid, &attr, runner1, NULL);

    // Immediately send a cancellation request to the thread
    pthread_cancel(tid);

    // Print the sum value (may not be complete!)
    printf("\nsum = %lu\n", sum);

    // Print that main thread is done
    printf("\nMain Thread Done, PID = %d\n", getpid());
}
