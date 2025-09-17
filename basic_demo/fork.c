// demo code, fork 3 times

#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("Hello from process %d\n", getpid());
    return 0;
}