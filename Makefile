all: base

base: src/base.c src/element.c
	$(CC) -o $@ $^ -lm

clean:
	rm -f base

.PHONY: all clean
