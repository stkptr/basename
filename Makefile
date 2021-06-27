CFLAGS = -Wall -Wpedantic

all: base

base: src/main.c src/base.c src/element.c src/elist.c src/trie.c
	$(CC) -o $@ $^ $(CFLAGS) -lm

clean:
	rm -f base

.PHONY: all clean
