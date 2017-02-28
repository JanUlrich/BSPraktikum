#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "mutex.h"

void *thread1();
void *thread2();

int test = 0;

int main(int argc, char **argv)
{
  pthread_t p1, p2;
  do{
  	test = 0;
  	pthread_create(&p1,NULL,thread1,NULL);
  	pthread_create(&p2,NULL,thread2,NULL);
  	pthread_join(p1,NULL);
  	pthread_join(p2,NULL);
  }while(test==0);
  //Diese Ausgabe darf es nie geben:
  	printf("%d\n",test);
  return EXIT_SUCCESS;
}

void *thread1(){
  mutex_lock();
  for(int i=0;i<100;i++)test++;
  mutex_unlock();
  pthread_exit(EXIT_SUCCESS);
}

void *thread2(){
  mutex_lock();
  for(int i=0;i<100;i++)test--;
  mutex_unlock();
  pthread_exit(EXIT_SUCCESS);
}