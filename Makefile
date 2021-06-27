CFLAGS = -Wall -Wpedantic

DEPS = src/main.o src/base.o src/element.o src/elist.o

all: name parse

name: $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

parse: $(DEPS) src/trie.o
	$(CC) -o $@ $^ $(CFLAGS) -lm

%.o: src/%.c
	$(CC) -c $@ $^ $(CFLAGS)

clean:
	rm -f base src/*.o

.PHONY: all clean
