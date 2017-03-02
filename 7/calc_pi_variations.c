#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

// Zuerst die sequentielle Addition

double Untersumme_seq(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    for (int i=1; i<=stripes; i=i+1){
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
    }
 
    return 4*Ergebnis;
}

double Obersumme_seq(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    for (int i=0; i<=(stripes-1); i++){
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
    }
 
    return 4*Ergebnis;
}

// OpenMP critical kann jeden Codeblock umfassen, erzeugt aber einen großen overhead 
// (beansprucht vor allem Platz für jeden Thread)

double Untersumme_crit(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    #pragma omp parallel for
    for (int i=1; i<=stripes; i=i+1){
      #pragma omp critical
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
    }
 
    return 4*Ergebnis;
}

double Obersumme_crit(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    #pragma omp parallel for
    for (int i=0; i<=(stripes-1); i++)
      #pragma omp critical
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
 
    return 4*Ergebnis;
}

// Atomares OpenMP lockt auf atomarer Ebene (durch Inkrementation zB) 
// den Prozess an einen kritischen Bereich. Nachteil: Das Instruktionenset ist
// beschränkt (arithmetische OP zB)

double Obersumme_atom(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    #pragma omp parallel for
    for (int i=0; i<=(stripes-1); i++)
      #pragma omp atomic
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
 
    return 4*Ergebnis;
}

double Untersumme_atom(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    #pragma omp parallel for
    for (int i=1; i<=stripes; i=i+1){
      #pragma omp atomic
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
    }
 
    return 4*Ergebnis;
}

// OpenMP reduction

double Obersumme_red(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    #pragma omp parallel for \
      reduction(+:Ergebnis)
    for (int i=0; i<=(stripes-1); i++)
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
 
    return 4*Ergebnis;
}

double Untersumme_red(int stripes)
{
    double n = stripes;
    double Ergebnis=0;
    #pragma omp parallel for \
      reduction(+:Ergebnis)
    for (int i=1; i<=stripes; i=i+1){
      Ergebnis = Ergebnis + (1/n)*sqrt(1-pow(i/n,2));
    }
 
    return 4*Ergebnis;
}