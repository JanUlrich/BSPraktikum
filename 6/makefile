CC=gcc
CFLAGS=-Wall -std=c99 -pthread
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) -c mutex.c -o mutex.o
	$(CC) $(CFLAGS) $(DEBUG) test_mutex.c mutex.c tsl.o -o test_mutex
	$(CC) -O2 -S -o test.s test.c
	as -o my_tsl.o my_tsl.s
	$(CC) $(CFLAGS) $(DEBUG) -c my_mutex.c -o my_mutex.o
	$(CC) $(CFLAGS) $(DEBUG) test_my_mutex.c my_mutex.c my_tsl.o -o test_my_mutex
stable:
	$(CC) $(CFLAGS) $(RELEASE) test_mutex.c mutex.c tsl.o -o test_mutex
clean:
	rm -vfr *~ 
