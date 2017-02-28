CC=gcc
CFLAGS=-Wall -std=c99 -pthread
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) matrix.c -o matrix
	$(CC) $(CFLAGS) $(DEBUG) posix.c -o posix
stable:
	$(CC) $(CFLAGS) $(RELEASE) matrix.c -o matrix
	$(CC) $(CFLAGS) $(RELEASE) posix.c -o posix
clean:
	rm -vfr *~ 