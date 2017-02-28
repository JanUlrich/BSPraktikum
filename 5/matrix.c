#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <alloca.h>

#define MAX_THREADS 4

void *thread();
void squareVersion1(int** input, int** output, int n);
void squareVersion2(int** input, int** output, int n);
void randomMatrix(int** matrix, int n);
void printMatrix(int** matrix, int n);
void calcMatrix(int** input, int** output, int n, int i, int j);
void *calcMatrixThread(void *args);
void *calcMatrixThreadVersion2(void *args);
pthread_t encode(int** input, int** output, int n, int i, int j);

struct arg_struct {
    int n;
    int i;
    int j;
    int** input;
    int** output;
};

int main(int argc, char **argv)
{
	int n = 5;
	int* input[n];//alloca(sizeof(void*)*n*n);
	for(int i = 0; i<n;i++){
		input[i] = alloca(sizeof(int)*n);
	}
	randomMatrix(input, n);

	printf("Eingabematrix:\n");
	printMatrix(input,n);

	int* output[n];//alloca(sizeof(void*)*n*n);
	for(int i = 0; i<n;i++){
		output[i] = alloca(sizeof(int)*n);
	}

	printf("\nMethode 1:\n");
	squareVersion1(input, output, n);
	printMatrix(output, n);

	randomMatrix(output, n); //Reset output Matrix

	printf("\nMethode 2:\n");
	squareVersion2(input, output, n);
	printMatrix(output, n);

	return EXIT_SUCCESS;
}

void squareVersion1(int** input, int** output, int n){
	pthread_t threads[n*n];
	struct arg_struct * argPointer[n*n];
	int numThreads = 0;
	for(int i = 0;i<n;i++)for(int j = 0;j<n;j++){
		struct arg_struct *arg = malloc(sizeof(struct arg_struct));

		arg->input = input;
		arg->output = output;
		arg->n = n;
		arg->i=i;
		arg->j=j;

		pthread_t thread;
		pthread_create(&thread,NULL,calcMatrixThread,arg);

		threads[numThreads] = thread;
		argPointer[numThreads] = arg;
		numThreads++;
	}
	
	for(int i=0;i<numThreads;i++){
		pthread_join(threads[i],NULL);
		free(argPointer[i]);
	}
}

void squareVersion2(int** input, int** output, int n){
	int rowsInThread[MAX_THREADS];
	for(int i = 0; i<MAX_THREADS;i++){
		rowsInThread[i]=n/MAX_THREADS;
	}
	int oddRows = n%MAX_THREADS;
	for(int i = 0;  i<oddRows;i++){
		rowsInThread[i] += 1;
	}

	pthread_t threads[MAX_THREADS];
	struct arg_struct * argPointer[MAX_THREADS];
	int i = 0;
	for(int numThreads = 0;numThreads<MAX_THREADS;numThreads++){
		struct arg_struct *arg = malloc(sizeof(struct arg_struct));
		arg->input = input;
		arg->output = output;
		arg->n = n;
		arg->i=i;
		arg->j=rowsInThread[numThreads];

		i+=rowsInThread[numThreads];

		pthread_t thread;
		pthread_create(&thread,NULL,calcMatrixThreadVersion2,arg);

		threads[numThreads] = thread;
		argPointer[numThreads] = arg;
	}

	for(int numThreads=0;i<MAX_THREADS;numThreads++){
		pthread_join(threads[numThreads],NULL);
		free(argPointer[numThreads]);
	}
}

void *calcMatrixThread(void *args){
	struct arg_struct *argStruct = (struct arg_struct*) args;
	calcMatrix(argStruct->input,argStruct->output, argStruct->n, argStruct->i, argStruct->j);

	pthread_exit(EXIT_SUCCESS);
}

void *calcMatrixThreadVersion2(void *args){
	struct arg_struct *argStruct = (struct arg_struct*) args;
	for(int i = argStruct->i;i<argStruct->i+argStruct->j;i++)
	for(int j = 0;j<argStruct->n;j++){
		calcMatrix(argStruct->input,argStruct->output, argStruct->n, i, j);
	}
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