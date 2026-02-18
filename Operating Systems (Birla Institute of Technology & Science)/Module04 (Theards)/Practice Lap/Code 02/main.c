#include <stdio.h>      // Provides printf()
#include <unistd.h>     // Provides getpid()
#include <pthread.h>    // Provides Pthreads API

// Function executed by each thread
void *runner1(void *param)
{
    pthread_t td;   // Variable to store the thread ID

    // param is received as void*
    // We passed &tid[i] from main (address of a pthread_t variable)
    // So we cast param to (pthread_t *) and dereference it
    // to obtain the actual thread ID value
    td = *(pthread_t *)param;

    // Print the thread ID
    // Cast to unsigned long for portable printing
    printf("\nThread ID = %lu\n", (unsigned long)td);

    // Terminate the thread normally
    pthread_exit(0);
}

int main()
{
    pthread_t tid[20];      // Array to store 20 thread IDs
    pthread_attr_t attr;    // Thread attribute object

    // Initialize thread attributes with default values
    pthread_attr_init(&attr);

    // Create 20 threads
    for(int i = 0; i < 20; i++)
        // &tid[i] → where the thread ID will be stored
        // &attr → thread attributes (default settings)
        // runner1 → function each thread executes
        // &tid[i] → argument passed to the thread function
        pthread_create(&tid[i], &attr, runner1, &tid[i]);

    // Wait for all 20 threads to complete
    for(int i = 0; i < 20; i++)
        pthread_join(tid[i], NULL);

    // This line executes only after all threads finish
    printf("\nMain Thread Done, PID = %d\n", getpid());
}
