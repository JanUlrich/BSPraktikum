#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "calc_pi_variations.h"

int main(int argc, char **argv){
	int stripes;
	void getparams(int argc, char **argv, int *stripes);
	Obersumme_seq(stripes);
	Obersumme_seq(10);
}



void getparams(int argc, char **argv, int *stripes)
{
  int opterrflag = 0;

  if (argc > 1) {
    *stripes = atoi(argv[1]);
  } else {
    opterrflag = 1;
  }

  if (opterrflag) {
    fprintf(stderr,
            "Benutzung:\n"
            "\n"
            "  %s <Anzahl Streifen>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}