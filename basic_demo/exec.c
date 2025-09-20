#include <stdio.h>
#include <unistd.h>

int main() {
    char *argv[] = { "echo", "this", "is", "echo", NULL };
    execvp("echo", argv);
    // If execvp is successful, the following line will not be executed
    printf("execvp failed\n");
    return 0;
}