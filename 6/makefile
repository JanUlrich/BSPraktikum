CC=gcc
CFLAGS=-Wall -std=c99 -pthread
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) test_mutex.c mutex.c tsl.o -o test_mutex
stable:
	$(CC) $(CFLAGS) $(RELEASE) test_mutex.c mutex.c tsl.o -o test_mutex
clean:
	rm -vfr *~ 
