#include <stdio.h>
#include <unistd.h>

int main(){
    if(fork() == 0)  // Child process only
        printf("\nBAD\n");  // Only child prints "BAD"

    printf("\nHELLO\n");  // Both parent and child print "HELLO"
    return 0;
}
