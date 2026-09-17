# generate executables from C source files
# usage: make or make <target name>


# output directory for compiled binaries
BUILD_DIR := build
SOURCES := $(wildcard *.c)
TARGETS := $(SOURCES:.c=)
BINARIES := $(addprefix $(BUILD_DIR)/,$(TARGETS))

.PHONY: all clean run

all: $(BUILD_DIR) $(BINARIES)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%: %.c | $(BUILD_DIR)
	gcc $< -o $@

run:
	@target="$(word 2,$(MAKECMDGOALS))"; \
	if [ -z "$$target" ]; then \
		echo "Usage: make run <target>"; \
		exit 1; \
	fi; \
	$(MAKE) --always-make $(BUILD_DIR)/$$target && ./$(BUILD_DIR)/$$target

%:
	@:

clean:
	rm -f $(BINARIES)
