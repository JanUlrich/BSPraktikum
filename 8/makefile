CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) signal.c -o signal
stable:
	$(CC) $(CFLAGS) $(RELEASE) signal.c -o signal
clean:
	rm -vfr *~ 
