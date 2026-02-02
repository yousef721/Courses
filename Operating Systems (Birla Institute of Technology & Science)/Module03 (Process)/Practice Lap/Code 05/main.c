#include <stdio.h>
#include <unistd.h>

int main(){
    int x = 10;

    if(fork() != 0){  // Parent process
        x = x + 10;  // Parent changes its own x
        printf("\nPARENT:: %d\n", x); // Prints 20
    }
    else{  // Child process
        sleep(3);  // Wait 3 seconds to let parent run first
        printf("\nChild:: %d\n", x);  // Prints 10 (child has its own copy of x)
    }

    return 0;
}
