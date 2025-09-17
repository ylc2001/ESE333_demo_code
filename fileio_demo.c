/*
 * ESE333 Demo Code - File I/O Operations
 * Demonstrates: fgets(), fputs(), open(), close()
 * 
 * This program shows different ways to read and write files using
 * both high-level stdio functions and low-level system calls.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void demo_stdio_operations() {
    printf("=== Stdio Operations Demo (fgets/fputs) ===\n");
    
    const char *filename = "demo_file.txt";
    FILE *file;
    char buffer[256];
    
    // Write to file using fputs
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen for writing failed");
        return;
    }
    
    fputs("Line 1: Hello from ESE333!\n", file);
    fputs("Line 2: This is a demo file.\n", file);
    fputs("Line 3: Testing fgets and fputs.\n", file);
    fclose(file);
    printf("Data written to %s using fputs\n", filename);
    
    // Read from file using fgets
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen for reading failed");
        return;
    }
    
    printf("Reading file contents using fgets:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read: %s", buffer);  // fgets includes the newline
    }
    fclose(file);
    printf("\n");
}

void demo_lowlevel_operations() {
    printf("=== Low-level Operations Demo (open/close) ===\n");
    
    const char *filename = "lowlevel_demo.txt";
    int fd;
    const char *data = "Hello from low-level I/O!\nThis uses open/write/read/close.\n";
    char buffer[256];
    ssize_t bytes_written, bytes_read;
    
    // Open file for writing (create if doesn't exist, truncate if exists)
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for writing failed");
        return;
    }
    
    // Write data
    bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return;
    }
    printf("Wrote %zd bytes to %s\n", bytes_written, filename);
    close(fd);
    
    // Open file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open for reading failed");
        return;
    }
    
    // Read data
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read failed");
        close(fd);
        return;
    }
    buffer[bytes_read] = '\0';  // Null-terminate
    printf("Read %zd bytes:\n%s", bytes_read, buffer);
    close(fd);
    printf("\n");
}

void demo_file_copying() {
    printf("=== File Copying Demo ===\n");
    
    const char *source = "demo_file.txt";
    const char *dest = "copied_file.txt";
    FILE *src_file, *dest_file;
    char buffer[1024];
    size_t bytes_read;
    
    // Open source file for reading
    src_file = fopen(source, "r");
    if (src_file == NULL) {
        perror("Failed to open source file");
        return;
    }
    
    // Open destination file for writing
    dest_file = fopen(dest, "w");
    if (dest_file == NULL) {
        perror("Failed to open destination file");
        fclose(src_file);
        return;
    }
    
    // Copy file content
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }
    
    fclose(src_file);
    fclose(dest_file);
    printf("Copied %s to %s\n", source, dest);
    printf("\n");
}

void cleanup_demo_files() {
    printf("=== Cleanup ===\n");
    unlink("demo_file.txt");
    unlink("lowlevel_demo.txt");
    unlink("copied_file.txt");
    printf("Cleaned up demo files\n");
}

int main() {
    printf("ESE333 File I/O Operations Demo\n");
    printf("===============================\n\n");
    
    demo_stdio_operations();
    demo_lowlevel_operations();
    demo_file_copying();
    cleanup_demo_files();
    
    printf("All file I/O demos completed!\n");
    return 0;
}