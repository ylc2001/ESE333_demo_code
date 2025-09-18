

This folder contains demo C programs showcasing common system operations and system calls that are fundamental to understanding Unix/Linux programming.

## Demo Programs

### 1. Process Operations (`process_demo.c`)
Demonstrates the following system calls:
- **`fork()`** - Create child processes
- **`execvp()`** - Execute programs in child processes
- **`exit()`** - Terminate processes with exit codes
- **`waitpid()`** - Wait for child process completion and get exit status

**Features:**
- Basic fork and parent-child communication
- Program execution with command-line arguments
- Multiple child process management
- Exit status handling

### 2. File I/O Operations (`fileio_demo.c`)
Demonstrates the following functions:
- **`fgets()`** - Read lines from files (high-level I/O)
- **`fputs()`** - Write strings to files (high-level I/O)
- **`open()`** - Open files (low-level I/O)
- **`close()`** - Close file descriptors (low-level I/O)

**Features:**
- High-level stdio operations with FILE pointers
- Low-level system calls with file descriptors
- File creation, reading, and writing
- File copying example

### 3. Pipes and I/O Redirection (`pipe_demo.c`)
Demonstrates the following system calls:
- **`pipe()`** - Create pipes for inter-process communication
- **`dup2()`** - Duplicate file descriptors for I/O redirection

**Features:**
- Basic pipe communication between parent and child
- Command pipelining (e.g., `ls | wc -l`)
- File output redirection
- Bidirectional communication between processes

### 4. Directory Operations (`directory_demo.c`)
Demonstrates the following functions:
- **`getcwd()`** - Get current working directory
- **`chdir()`** - Change current working directory

**Features:**
- Getting and displaying current directory
- Changing directories programmatically
- Directory traversal examples
- Error handling for directory operations
- Dynamic memory allocation with getcwd

## Building and Running

### Prerequisites
- GCC compiler
- Make utility
- Unix/Linux environment (or WSL on Windows)

### Build All Programs
```bash
make all
```

### Run All Demos
```bash
make run-all
```

### Run Individual Demos
```bash
make run-process     # Process operations demo
make run-fileio      # File I/O operations demo
make run-pipe        # Pipes and redirection demo
make run-directory   # Directory operations demo
```

### Clean Up
```bash
make clean
```

### Help
```bash
make help
```

## Learning Objectives

These demos help students understand:

1. **Process Management**: How Unix processes are created, managed, and coordinated
2. **File System Interaction**: Different levels of file I/O and their appropriate use cases
3. **Inter-Process Communication**: Using pipes to connect processes and build complex command pipelines
4. **File System Navigation**: Programmatic directory operations and path management
5. **Error Handling**: Proper error checking and handling for system calls
6. **Resource Management**: Proper cleanup of file descriptors, processes, and temporary files

## System Calls Reference

| System Call | Purpose | Demo File |
|-------------|---------|-----------|
| `fork()` | Create child process | `process_demo.c` |
| `execvp()` | Execute program | `process_demo.c` |
| `exit()` | Terminate process | `process_demo.c` |
| `waitpid()` | Wait for child | `process_demo.c` |
| `fgets()` | Read line from file | `fileio_demo.c` |
| `fputs()` | Write string to file | `fileio_demo.c` |
| `open()` | Open file | `fileio_demo.c` |
| `close()` | Close file descriptor | `fileio_demo.c` |
| `pipe()` | Create pipe | `pipe_demo.c` |
| `dup2()` | Duplicate file descriptor | `pipe_demo.c` |
| `getcwd()` | Get current directory | `directory_demo.c` |
| `chdir()` | Change directory | `directory_demo.c` |

## Notes for Students

- Each demo program is self-contained and can be studied independently
- Comments in the code explain the purpose and behavior of each system call
- Error handling is demonstrated throughout to show proper programming practices
- The demos create temporary files and directories but clean them up automatically
- Run the programs in a terminal to see the full output and behavior
