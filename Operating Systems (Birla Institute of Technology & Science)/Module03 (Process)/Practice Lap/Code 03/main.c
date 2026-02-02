#include <stdio.h>
#include <unistd.h>

int main(){
    if(fork() != 0){  // Parent process
        execlp("/bin/rm", "rm", "abc.txt", NULL);  // Replace parent process image with rm
        printf("\nAFTER EXEC\n");  // This line will NOT execute if execlp succeeds
    }
    else{  // Child process
        sleep(3);  // Delay execution
        printf("\nBYE\n");  // Child prints "BYE"
    }

    printf("\nTHE END\n");  // Both parent (if execlp fails) and child print this
    return 0;
}
