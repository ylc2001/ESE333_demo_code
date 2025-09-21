/*
 * ESE333 Demo Code - Directory Operations
 * Demonstrates: getcwd(), chdir()
 * 
 * This program shows how to get the current working directory
 * and how to change directories programmatically.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void print_current_directory(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd failed");
    }
}

void demo_getcwd_basic(void) {
    printf("=== Basic getcwd Demo ===\n");
    print_current_directory();
    printf("\n");
}

void demo_chdir_operations(void) {
    printf("=== Directory Changing Demo ===\n");
    
    char original_dir[1024];
    
    // Save original directory
    if (getcwd(original_dir, sizeof(original_dir)) == NULL) {
        perror("getcwd failed");
        return;
    }
    printf("Starting directory: %s\n", original_dir);
    
    // Create a test directory
    const char *test_dir = "test_directory";
    if (mkdir(test_dir, 0755) == -1) {
        if (errno != EEXIST) {
            perror("mkdir failed");
            return;
        }
    }
    printf("Created directory: %s\n", test_dir);
    
    // Change to the test directory
    if (chdir(test_dir) == -1) {
        perror("chdir failed");
        return;
    }
    printf("Changed to test directory\n");
    print_current_directory();
    
    // Try to change to parent directory using ".."
    if (chdir("..") == -1) {
        perror("chdir to parent failed");
        return;
    }
    printf("Changed back to parent directory\n");
    print_current_directory();
    
    // Clean up - remove test directory
    if (rmdir(test_dir) == -1) {
        perror("rmdir failed");
    } else {
        printf("Removed test directory\n");
    }
    printf("\n");
}

void demo_directory_traversal(void) {
    printf("=== Directory Traversal Demo ===\n");
    
    char original_dir[1024];
    
    // Save original directory
    if (getcwd(original_dir, sizeof(original_dir)) == NULL) {
        perror("getcwd failed");
        return;
    }
    
    // Create nested directory structure
    mkdir("level1", 0755);
    mkdir("level1/level2", 0755);
    mkdir("level1/level2/level3", 0755);
    printf("Created nested directory structure\n");
    
    // Navigate through the directories
    printf("Traversing directories:\n");
    
    if (chdir("level1") == 0) {
        print_current_directory();
        
        if (chdir("level2") == 0) {
            print_current_directory();
            
            if (chdir("level3") == 0) {
                print_current_directory();
                
                // Go back to original directory
                if (chdir(original_dir) == 0) {
                    printf("Returned to original directory\n");
                    print_current_directory();
                }
            }
        }
    }
    
    // Clean up directory structure
    rmdir("level1/level2/level3");
    rmdir("level1/level2");
    rmdir("level1");
    printf("Cleaned up directory structure\n");
    printf("\n");
}

void demo_getcwd_with_different_sizes(void) {
    printf("=== getcwd with Different Buffer Sizes Demo ===\n");
    
    // Try with small buffer (this might fail for long paths)
    char small_buffer[10];
    printf("Trying getcwd with small buffer (size 10):\n");
    if (getcwd(small_buffer, sizeof(small_buffer)) != NULL) {
        printf("Success: %s\n", small_buffer);
    } else {
        printf("Failed (expected for long paths): %s\n", strerror(errno));
    }
    
    // Try with adequate buffer
    char adequate_buffer[1024];
    printf("Trying getcwd with adequate buffer (size 1024):\n");
    if (getcwd(adequate_buffer, sizeof(adequate_buffer)) != NULL) {
        printf("Success: %s\n", adequate_buffer);
    } else {
        printf("Failed: %s\n", strerror(errno));
    }
    
    // Using dynamic allocation (getcwd with NULL)
    printf("Using getcwd with dynamic allocation:\n");
    char *dynamic_cwd = getcwd(NULL, 0);
    if (dynamic_cwd != NULL) {
        printf("Success: %s\n", dynamic_cwd);
        free(dynamic_cwd);  // Don't forget to free!
    } else {
        printf("Failed: %s\n", strerror(errno));
    }
    printf("\n");
}

void demo_error_handling(void) {
    printf("=== Error Handling Demo ===\n");
    
    // Try to change to a non-existent directory
    printf("Attempting to change to non-existent directory:\n");
    if (chdir("/this/directory/does/not/exist") == -1) {
        printf("chdir failed as expected: %s\n", strerror(errno));
    }
    
    // Try to change to a file instead of directory
    printf("Creating a file and trying to chdir to it:\n");
    FILE *file = fopen("test_file.txt", "w");
    if (file) {
        fputs("This is a test file\n", file);
        fclose(file);
        
        if (chdir("test_file.txt") == -1) {
            printf("chdir to file failed as expected: %s\n", strerror(errno));
        }
        
        unlink("test_file.txt");  // Clean up
    }
    printf("\n");
}

int main(void) {
    printf("ESE333 Directory Operations Demo\n");
    printf("================================\n\n");
    
    demo_getcwd_basic();
    demo_chdir_operations();
    demo_directory_traversal();
    demo_getcwd_with_different_sizes();
    demo_error_handling();
    
    printf("All directory operation demos completed!\n");
    return 0;
}
