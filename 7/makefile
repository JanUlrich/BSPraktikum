CC=gcc
CFLAGS=-Wall -std=c99 -pthread -lm
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_sequential.c -o calc_pi_sequential
stable:
	$(CC) $(CFLAGS) $(RELEASE) calc_pi_sequential.c -o calc_pi_sequential
clean:
	rm -vfr *~ 
