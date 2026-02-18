#include <stdio.h>      // For printf()
#include <unistd.h>     // For getpid()
#include <pthread.h>    // For pthreads API

// Function executed by each thread
void *runner1(void *param){
    pthread_t td;

    // Cast the void* param to pthread_t
    // WARNING: This is not a safe way to pass pthread_t; we'll discuss below
    td = *(pthread_t *)(param);

    // Print the thread ID
    printf("\nThread ID = %lu\n", (unsigned long)td);

    // Terminate the thread normally
    pthread_exit(0);
}

int main()
{
    pthread_t tid1, tid2, tid3;      // Thread identifiers
    pthread_attr_t attr;             // Thread attribute object

    pthread_attr_init(&attr);        // Initialize attributes with default values

    // Create two threads
    pthread_create(&tid1, &attr, runner1, &tid1);  // Thread 1 executes runner1
    pthread_create(&tid2, &attr, runner1, &tid2);  // Thread 2 executes runner1

    // Compare tid1 and tid2
    // Returns 1 if equal, 0 if not
    printf("\n1:: %d\n", pthread_equal(tid1, tid2));

    // Get thread ID of the calling thread (main thread)
    tid3 = pthread_self();

    // Compare tid3 with current thread (main thread)
    printf("\n2:: %d\n", pthread_equal(tid3, pthread_self()));

    // Wait for both threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Print main thread info
    printf("\nMain Thread Done, PID = %d\n", getpid());
}
