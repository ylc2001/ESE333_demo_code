# ESE333 Demo Code Makefile
# Builds all demo programs for common system operations

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGETS = process_demo fileio_demo pipe_demo directory_demo

# Default target - build all demos
all: $(TARGETS)

# Individual targets
process_demo: process_demo.c
	$(CC) $(CFLAGS) -o $@ $<

fileio_demo: fileio_demo.c
	$(CC) $(CFLAGS) -o $@ $<

pipe_demo: pipe_demo.c
	$(CC) $(CFLAGS) -o $@ $<

directory_demo: directory_demo.c
	$(CC) $(CFLAGS) -o $@ $<

# Run all demos
run-all: all
	@echo "=== Running Process Demo ==="
	./process_demo
	@echo
	@echo "=== Running File I/O Demo ==="
	./fileio_demo
	@echo
	@echo "=== Running Pipe Demo ==="
	./pipe_demo
	@echo
	@echo "=== Running Directory Demo ==="
	./directory_demo

# Run individual demos
run-process: process_demo
	./process_demo

run-fileio: fileio_demo
	./fileio_demo

run-pipe: pipe_demo
	./pipe_demo

run-directory: directory_demo
	./directory_demo

# Clean up compiled programs and temporary files
clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f demo_file.txt lowlevel_demo.txt copied_file.txt output.txt

# Help target
help:
	@echo "ESE333 Demo Code - Available targets:"
	@echo "  all          - Build all demo programs"
	@echo "  clean        - Remove compiled programs and temporary files"
	@echo "  run-all      - Build and run all demos"
	@echo "  run-process  - Build and run process operations demo"
	@echo "  run-fileio   - Build and run file I/O operations demo"
	@echo "  run-pipe     - Build and run pipe and redirection demo"
	@echo "  run-directory- Build and run directory operations demo"
	@echo "  help         - Show this help message"

.PHONY: all clean run-all run-process run-fileio run-pipe run-directory help