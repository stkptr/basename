CFLAGS = -Wall -Wpedantic

all: base

base: src/base.c src/element.c src/elist.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f base

.PHONY: all clean
