#include <stdio.h>      // Provides printf() function
#include <unistd.h>     // Provides getpid() function
#include <pthread.h>    // Provides POSIX threads API

// Function executed by each thread
void *runner1(void *param){
    int *p;                 // Pointer to an integer

    // Cast the void* argument to int*
    p = (int *)(param);

    // Print the integer value pointed by p
    printf("\n%d\n", *p);

    // Terminate the thread
    pthread_exit(0);
}

int main(){
    pthread_t tid[20];      // Array to store 20 thread IDs
    int arr[20];            // Array to store 20 integer values

    // Initialize the array with values 10, 20, ..., 200
    for(int i = 0; i < 20; i++)
        arr[i] = (i + 1) * 10;

    pthread_attr_t attr;    // Thread attribute object
    pthread_attr_init(&attr); // Initialize default attributes

    // Create 20 threads
    for(int i = 0; i < 20; i++){
        if(i % 2 == 0)
            // For even indices: pass the address of arr[i]
            pthread_create(&tid[i], &attr, runner1, &arr[i]);
        else{
            // For odd indices: create a temporary variable x
            int x = arr[i] - 1000;
            // Pass its address to the thread
            pthread_create(&tid[i], &attr, runner1, &x);
            // ⚠ BUG: 'x' is a local variable that goes out of scope after this iteration
            // The thread may read garbage value because the memory might be overwritten
        }
    }

    // Wait for all threads to finish
    for(int i = 0; i < 20; i++)
        pthread_join(tid[i], NULL);

    printf("\nMain Thread Done, PID = %d\n", getpid());
}
