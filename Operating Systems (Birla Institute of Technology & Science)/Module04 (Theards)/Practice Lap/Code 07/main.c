#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

unsigned long sum = 0;            // Shared variable
pthread_mutex_t lock;              // Mutex for safe access

void *runner1(void *param) {
    for (unsigned long i = 0; i < 1000000; i++) {
        pthread_testcancel();      // Cancellation point: check if thread should terminate

        // Lock mutex before updating sum
        pthread_mutex_lock(&lock);
        sum += i;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;

    pthread_mutex_init(&lock, NULL);          // Initialize mutex
    pthread_attr_init(&attr);                 // Default thread attributes

    pthread_create(&tid, &attr, runner1, NULL);  // Create thread

    // Let the thread run for a short time, then cancel
    usleep(10);                                // Sleep for microseconds
    pthread_cancel(tid);                        // Request cancellation

    pthread_join(tid, NULL);                    // Wait for thread to terminate

    printf("\nSum = %lu\n", sum);
    printf("Main Thread Done, PID = %d\n", getpid());

    pthread_mutex_destroy(&lock);              // Clean up mutex
    return 0;
}
