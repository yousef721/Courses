#include <stdio.h>
#include <unistd.h>

int main(){
    fork();  // Creates 1 child -> total 2 processes
    fork();  // Each of the 2 processes creates a child -> total 4 processes
    fork();  // Each of the 4 processes creates a child -> total 8 processes
    fork();  // Each of the 8 processes creates a child -> total 16 processes

    printf("\nHELLO:: %d\n", getpid()); // Each process prints its PID
    return 0;
}
