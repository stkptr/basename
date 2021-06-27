CFLAGS = -Wall -Wpedantic

# main.c for the macros to work
DEPS = src/main.c src/base.o src/element.o src/elist.o

all: name parse hyphenate

name: $(DEPS)
	$(CC) -o $@ -DNAME $^ $(CFLAGS) -lm

parse: $(DEPS) src/trie.o
	$(CC) -o $@ -DPARSE $^ $(CFLAGS) -lm

hyphenate: $(DEPS) src/trie.o
	$(CC) -o $@ -DHYPHEN $^ $(CFLAGS) -lm

%.o: src/%.c
	$(CC) -c $@ $^ $(CFLAGS)

clean:
	rm -f base src/*.o

.PHONY: all clean
