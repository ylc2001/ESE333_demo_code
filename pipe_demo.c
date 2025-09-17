/*
 * ESE333 Demo Code - Pipes and I/O Redirection
 * Demonstrates: pipe(), dup2()
 * 
 * This program shows how to create pipes for inter-process communication
 * and how to redirect stdin/stdout using dup2.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

void demo_basic_pipe() {
    printf("=== Basic Pipe Demo ===\n");
    
    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Hello through pipe!";
    char read_buffer[100];
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return;
    }
    
    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return;
    } else if (pid == 0) {
        // Child process - writer
        close(pipefd[0]);  // Close read end
        printf("Child writing to pipe: %s\n", write_msg);
        write(pipefd[1], write_msg, strlen(write_msg));
        close(pipefd[1]);
        exit(0);
    } else {
        // Parent process - reader
        close(pipefd[1]);  // Close write end
        ssize_t bytes_read = read(pipefd[0], read_buffer, sizeof(read_buffer) - 1);
        read_buffer[bytes_read] = '\0';
        printf("Parent read from pipe: %s\n", read_buffer);
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
    printf("\n");
}

void demo_pipe_with_exec() {
    printf("=== Pipe with Exec Demo (ls | wc -l) ===\n");
    
    int pipefd[2];
    pid_t pid1, pid2;
    
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return;
    }
    
    // First child: execute 'ls'
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        return;
    } else if (pid1 == 0) {
        // Child 1: ls
        close(pipefd[0]);  // Close read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);
        execlp("ls", "ls", NULL);
        perror("execlp ls failed");
        exit(1);
    }
    
    // Second child: execute 'wc -l'
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        return;
    } else if (pid2 == 0) {
        // Child 2: wc -l
        close(pipefd[1]);  // Close write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
        close(pipefd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc failed");
        exit(1);
    }
    
    // Parent closes both ends and waits
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    printf("\n");
}

void demo_dup2_file_redirection() {
    printf("=== dup2 File Redirection Demo ===\n");
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return;
    } else if (pid == 0) {
        // Child process: redirect output to file
        int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open failed");
            exit(1);
        }
        
        printf("This message goes to terminal (before redirection)\n");
        
        // Redirect stdout to file
        dup2(fd, STDOUT_FILENO);
        close(fd);
        
        printf("This message goes to file (after redirection)\n");
        printf("Another line in the file\n");
        exit(0);
    } else {
        // Parent waits and then displays file contents
        waitpid(pid, NULL, 0);
        printf("Child completed. File contents:\n");
        
        // Display what was written to the file
        FILE *file = fopen("output.txt", "r");
        if (file) {
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), file)) {
                printf("File: %s", buffer);
            }
            fclose(file);
            unlink("output.txt");  // Clean up
        }
    }
    printf("\n");
}

void demo_bidirectional_pipe() {
    printf("=== Bidirectional Communication Demo ===\n");
    
    int pipe1[2], pipe2[2];  // pipe1: parent->child, pipe2: child->parent
    pid_t pid;
    
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        return;
    }
    
    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return;
    } else if (pid == 0) {
        // Child process
        close(pipe1[1]);  // Close write end of pipe1
        close(pipe2[0]);  // Close read end of pipe2
        
        char buffer[100];
        ssize_t bytes_read = read(pipe1[0], buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';
        printf("Child received: %s\n", buffer);
        
        char response[] = "Hello back from child!";
        write(pipe2[1], response, strlen(response));
        
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe1[0]);  // Close read end of pipe1
        close(pipe2[1]);  // Close write end of pipe2
        
        char message[] = "Hello from parent!";
        write(pipe1[1], message, strlen(message));
        
        char buffer[100];
        ssize_t bytes_read = read(pipe2[0], buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';
        printf("Parent received: %s\n", buffer);
        
        close(pipe1[1]);
        close(pipe2[0]);
        waitpid(pid, NULL, 0);
    }
    printf("\n");
}

int main() {
    printf("ESE333 Pipes and I/O Redirection Demo\n");
    printf("=====================================\n\n");
    
    demo_basic_pipe();
    demo_pipe_with_exec();
    demo_dup2_file_redirection();
    demo_bidirectional_pipe();
    
    printf("All pipe and redirection demos completed!\n");
    return 0;
}