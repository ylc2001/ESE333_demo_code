/*
 * ESE333 Demo Code - Process Operations
 * Demonstrates: fork(), execvp(), exit(), waitpid()
 * 
 * This program shows how to create child processes, execute programs,
 * and wait for child completion.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void demo_fork_basic(void) {
    printf("=== Basic Fork Demo ===\n");
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(42);  // Exit with code 42
    } else {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    }
    printf("\n");
}

void demo_execvp(void) {
    printf("=== Execvp Demo ===\n");
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process - execute 'ls -l'
        printf("Child about to execute 'ls -l'\n");
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        // If we reach here, execvp failed
        perror("execvp failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent waiting for child to complete...\n");
        int status;
        waitpid(pid, &status, 0);
        printf("Child completed\n");
    }
    printf("\n");
}

void demo_multiple_children(void) {
    printf("=== Multiple Children Demo ===\n");
    const int num_children = 3;
    pid_t children[num_children];
    
    // Create multiple child processes
    for (int i = 0; i < num_children; i++) {
        children[i] = fork();
        
        if (children[i] == -1) {
            perror("fork failed");
            exit(1);
        } else if (children[i] == 0) {
            // Child process
            printf("Child %d: PID = %d, sleeping for %d seconds\n", i, getpid(), i + 1);
            sleep(i + 1);
            exit(i);
        }
    }
    
    // Parent waits for all children
    printf("Parent: Created %d children, waiting for completion...\n", num_children);
    for (int i = 0; i < num_children; i++) {
        int status;
        pid_t completed_pid = waitpid(children[i], &status, 0);
        if (WIFEXITED(status)) {
            printf("Child PID %d completed with exit status %d\n", 
                   completed_pid, WEXITSTATUS(status));
        }
    }
    printf("\n");
}

int main(void) {
    printf("ESE333 Process Operations Demo\n");
    printf("==============================\n\n");
    
    demo_fork_basic();
    demo_execvp();
    demo_multiple_children();
    
    printf("All demos completed!\n");
    return 0;
}
