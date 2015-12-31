CC = gcc
CFLAGS_common = -O0 -Wall -std=gnu99 -g

EXEC = recursive iterative

recursive: recursive.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

iterative: iterative.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

clean:
	rm -f $(EXEC) *.o perf.*
