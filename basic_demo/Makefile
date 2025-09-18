# generate executables from C source files
# usage: make or make <target name>


# output directory for compiled binaries
BUILD_DIR := build
SOURCES := $(wildcard *.c)
TARGETS := $(SOURCES:.c=)
BINARIES := $(addprefix $(BUILD_DIR)/,$(TARGETS))

all: $(BUILD_DIR) $(BINARIES)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%: %.c | $(BUILD_DIR)
	gcc $< -o $@

clean:
	rm -f $(BINARIES)
