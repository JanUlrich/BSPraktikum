#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "calc_pi_variations.h"

void getparams(int argc, char **argv, int *stripes);

int main(int argc, char **argv){
	int stripes;
	getparams(argc,argv,&stripes);
	printf("Lower Bound (sequential): %.7f\n",Untersumme_seq(stripes));
	printf("Upper Bound (sequential): %.7f\n",Obersumme_seq(stripes));

	printf("Lower Bound (crit): %.7f\n",Untersumme_crit(stripes));
	printf("Upper Bound (crit): %.7f\n",Obersumme_crit(stripes));

	printf("Lower Bound (atom): %.7f\n",Untersumme_atom(stripes));
	printf("Upper Bound (atom): %.7f\n",Obersumme_atom(stripes));

	printf("Lower Bound (red): %.7f\n",Untersumme_red(stripes));
	printf("Upper Bound (red): %.7f\n",Obersumme_red(stripes));
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