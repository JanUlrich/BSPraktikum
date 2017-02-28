#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread();

int main(int argc, char **argv)
{
  pthread_t p1;
  pthread_create(&p1,NULL,thread,NULL);
  pthread_join(p1,NULL);
  return EXIT_SUCCESS;
}

void *thread(){
  printf("new thread running\n");
}