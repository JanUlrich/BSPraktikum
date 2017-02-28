#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <alloca.h>

void *thread();
void square(int** input, int** output, int n);
void randomMatrix(int** matrix, int n);
void printMatrix(int** matrix, int n);
void calcMatrix(int** input, int** output, int n, int i, int j);
void *calcMatrixThread(void *args);
pthread_t encode(int** input, int** output, int n, int i, int j);

struct arg_struct {
    int arg1;
    int arg2;
};

int main(int argc, char **argv)
{
	int n = 3;
	int* input[n];//alloca(sizeof(void*)*n*n);
	for(int i = 0; i<n;i++){
		input[i] = alloca(sizeof(int)*n);
	}
	randomMatrix(input, n);
	//printMatrix(input,n);
	int* output[n];//alloca(sizeof(void*)*n*n);
	for(int i = 0; i<n;i++){
		output[i] = alloca(sizeof(int)*n);
	}
	square(input, output, n);
	printMatrix(output, n);
	return EXIT_SUCCESS;
}

void square(int** input, int** output, int n){
	int i;
	int j;
	for(i = 0;i<n;i++)for(j = 0;j<n;j++){
		//calcMatrix(input, output, n, i, j);
		void* args[6];
		args[0] = &input;
		args[1] = &output;
		args[2] = &n;
		args[3] = &i;
		args[4] = &j;
		args[5] = NULL;
		pthread_t thread;	
		pthread_create(&thread,NULL,calcMatrixThread,args);
		pthread_join(thread,NULL);
	}
	
}

void *calcMatrixThread(void *args){
	int** input = ((int***)args)[0];
	int** output = ((int***)args)[1];
	int n = ((int*)args)[2];
	int i = ((int*)args)[3];
	int j = ((int*)args)[4];
	calcMatrix(input,output, n, i, j);

	pthread_exit(EXIT_SUCCESS);
}

void calcMatrix(int** input, int** output, int n, int i, int j){
	(output[i])[j] = 0;
	for(int x = 0;x<n;x++){
		(output[i])[j] += (input[i])[x] * (input[x])[j];
	}
}

void randomMatrix(int** matrix, int n){
	for(int x = 0; x<n; x++)for(int y = 0; y<n; y++){
		(matrix[x])[y] = x+y;
	}
}


void printMatrix(int** matrix, int n){
	for(int x = 0; x<n; x++){
		for(int y = 0; y<n; y++){
			printf("% 7d ",(matrix[x])[y]);
		}
		printf("\n");
	}
}