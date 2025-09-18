# ESE333 Demo Code Makefile
# Builds all demo programs for common system operations


CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
BUILD_DIR = build
TARGETS = process_demo fileio_demo pipe_demo directory_demo
BINARIES = $(addprefix $(BUILD_DIR)/,$(TARGETS))

# Default target - build all demos
all: $(BUILD_DIR) $(BINARIES)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<


# Run all demos
run-all: all
	@echo "=== Running Process Demo ==="
	$(BUILD_DIR)/process_demo
	@echo
	@echo "=== Running File I/O Demo ==="
	$(BUILD_DIR)/fileio_demo
	@echo
	@echo "=== Running Pipe Demo ==="
	$(BUILD_DIR)/pipe_demo
	@echo
	@echo "=== Running Directory Demo ==="
	$(BUILD_DIR)/directory_demo


# Run individual demos
run-process: all
	$(BUILD_DIR)/process_demo

run-fileio: all
	$(BUILD_DIR)/fileio_demo

run-pipe: all
	$(BUILD_DIR)/pipe_demo

run-directory: all
	$(BUILD_DIR)/directory_demo


# Clean up compiled programs and temporary files
clean:
	rm -f $(BINARIES)
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