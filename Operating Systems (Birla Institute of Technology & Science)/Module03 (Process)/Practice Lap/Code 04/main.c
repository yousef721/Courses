#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  

int main(){
    if(fork() != 0){  // Parent process
        printf("\nPARENT:: %d\n", wait(NULL)); // Wait for child to finish, print child's PID
    }
    else{  // Child process
        printf("\nCHILD PID:: %d\n", getpid()); // Child prints its own PID
        sleep(3);  // Sleep for 3 seconds
        printf("\nChild:: %d\n", wait(NULL)); // Child has no children, wait returns -1
    }

    return 0;
}
