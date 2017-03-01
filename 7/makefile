CC=gcc
CFLAGS=-Wall -std=c99 -lm
DEBUG=-O0 -g
RELEASE=-O3
debug:
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_sequential.c -o calc_pi_sequential
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_critical.c -o calc_pi_critical -fopenmp 
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_atomic.c -o calc_pi_atomic -fopenmp 
	$(CC) $(CFLAGS) $(DEBUG) calc_pi_reduction.c -o calc_pi_reduction -fopenmp 
stable:
	$(CC) $(CFLAGS) $(RELEASE) calc_pi_sequential.c -o calc_pi_sequential
clean:
	rm -vfr *~ 
