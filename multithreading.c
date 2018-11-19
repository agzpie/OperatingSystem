#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// printf("Start number = %d\n", number);
// https://stackoverflow.com/questions/3908031/how-to-multithread-c-code
//  gcc -pthread multithreading.c -o multithreading.o

void *get_result(void *param)
{
	int *n = (int *)param;
	*n = (*n) * (*n);	
	
	//printf("n = %d\n", *n);
	
	return NULL;
}

int main()
{
  // Read how many numbers to square and sum?
	int ntimes = 3;

	pthread_t *tid = malloc( ntimes * sizeof(pthread_t) );
	int *results = malloc( ntimes * sizeof(int) );

	int i=0;
	for( i=0; i<ntimes; i++ ) 
	{
		int myNumber;
		// Reading 1-9, 0 to exit
		// 1. read char and cast to int
		printf("Write number: \n");
		scanf("%d", &myNumber);

		// 2. store it in *results
		results[i] = &myNumber;
		
		pthread_create(&tid[i], NULL, get_result, &myNumber );			
	}

	for( i=0; i<ntimes; i++ ) {
		pthread_join( tid[i], NULL );
	}

	int sum = 0;	
	// loop (for) over all numbers in *results and sum them.
// ERROR?
	for( i=0; i<ntimes; i++) {
		sum+=*results[i];
	}

	printf("Sum = %d\n", sum);	
}

