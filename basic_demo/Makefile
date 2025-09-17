# generate executables from C source files
# usage: make or make <target name>

SOURCES := $(wildcard *.c)
TARGETS := $(SOURCES:.c=)

all: $(TARGETS)

$(TARGETS): %: %.c
	gcc $< -o $@

clean:
	rm -f $(TARGETS)
