#include <stdio.h>      // For printf()
#include <unistd.h>     // For getpid()
#include <pthread.h>    // Pthreads library

// Function that will be executed by each thread
void *runner1(void *param)
{
    pthread_t td;   // Variable to store the thread ID

    // param is of type void*
    // We passed the address of a pthread_t variable
    // So we cast it to pthread_t* and dereference it
    td = *(pthread_t *)param;

    // Print the thread ID
    // Cast to unsigned long for portable printing
    printf("\nThread ID = %lu\n", (unsigned long)td);

    // Terminate the thread normally
    pthread_exit(0);
}

int main()
{
    pthread_t tid1, tid2;     // Variables to store thread IDs
    pthread_attr_t attr;      // Thread attribute object

    // Initialize thread attributes with default values
    pthread_attr_init(&attr);

    // Create first thread
    // &tid1 → where the thread ID will be stored
    // &attr → thread attributes
    // runner1 → function the thread will execute
    // &tid1 → argument passed to the thread function
    pthread_create(&tid1, &attr, runner1, &tid1);

    // Create second thread (same function, different ID storage)
    pthread_create(&tid2, &attr, runner1, &tid2);

    // Wait for first thread to finish
    pthread_join(tid1, NULL);

    // Wait for second thread to finish
    pthread_join(tid2, NULL);

    // This executes only after both threads have finished
    printf("\nMain Thread Done, PID = %d\n", getpid());

    return 0;
}
