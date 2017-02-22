CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) mycopy.c -o mycopy
	$(CC) $(CFLAGS) $(DEBUG) reverse.c -o reverse
stable:
	$(CC) $(CFLAGS) $(RELEASE) mycopy.c -o mycopy
	$(CC) $(CFLAGS) $(RELEASE) reverse.c -o reverse
clean:
	rm -vfr *~ 