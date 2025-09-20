#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid, status;

    pid = fork();
    if (pid == 0) {
        // In child process
        char *argv[] = {"echo", "child:", "THIS", "IS", "ECHO", NULL };
        execvp("echo", argv);
        printf("exec failed!\n");
        exit(1);
    } else if (pid > 0) {
        // In parent process
        printf("parent: waiting ...\n");
        wait(&status);
        printf("parent: the child exited with status %d\n", WEXITSTATUS(status));
    } else {
        perror("fork failed");
        exit(1);
    }

    exit(0);
}