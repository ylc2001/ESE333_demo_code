// demo code fork loop

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;
    for (i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0) {
            // In child process
            printf("i = %d, pid = %d, parent pid = %d\n", i, getpid(), getppid());
        }
    }
    wait(NULL);
    return 0;
}