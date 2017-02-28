#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char lock;

void mutex_lock(){
	while(tsl(&lock)==1);
}
void mutex_unlock(){
	lock = 0;
}

