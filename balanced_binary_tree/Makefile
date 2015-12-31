CC = gcc
CFLAGS_common = -O0 -Wall -std=gnu99 -g

EXEC = recursive

recursive: recursive.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

clean:
	rm -f $(EXEC) *.o perf.*
