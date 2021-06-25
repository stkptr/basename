all: base

base: base.c element.c
	$(CC) -o $@ $^ -lm

clean:
	rm -f base

.PHONY: all clean
