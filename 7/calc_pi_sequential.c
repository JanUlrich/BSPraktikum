#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <alloca.h>
#include <math.h>

void getparams(int argc, char **argv, int *stripes);
double Untersumme(double n);
double Obersumme(double n);

int main(int argc, char **argv)
{
	int stripes;
	getparams(argc, argv, &stripes);
	printf("Lower Bound: %.7f\n", Untersumme(stripes));
	printf("Upper Bound: %.7f\n", Obersumme(stripes));

	return EXIT_SUCCESS;
} 

double Untersumme(double n)
{
    double Ergebnis=0;
    for (int i=1; i<=n; i=i+1)
        Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
 
    return 4*Ergebnis;
}

double Obersumme(double n)
{
    double Ergebnis=0;
    for (int i=0; i<=(n-1); i++)
        Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
 
    return 4*Ergebnis;
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
