CC = gcc
CFLAGS_common = -O2 -Wall -std=gnu99 -g

EXEC = recursive iterative

all:$(EXEC)

recursive: recursive.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

iterative: iterative.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

clean:
	rm -f $(EXEC) *.o perf.*
