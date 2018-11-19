#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// https://stackoverflow.com/questions/3908031/how-to-multithread-c-code
//  gcc -pthread multithreading.c -o multithreading.o

void *get_result(void *param)  // param is a dummy pointer
{
	int *n = (int *)param;
	*n = *n+10;	

	return NULL;
}

int main()
{
	int ntimes = 3;

	pthread_t *tid = malloc( ntimes * sizeof(pthread_t) );
	//int *results = malloc( ntimes * sizeof(int) );

	int number = 2;
	
	int i=0;
	for( i=0; i<ntimes; i++ ) 
	{
		// Reading 1-9, 0 to exit
		// 1. read char and cast to int
		printf("number = %d\n", number);
		pthread_create(&tid[i], NULL, get_result, &number );
			
	}
	//... // do some tasks unrelated to result    

	for( i=0; i<ntimes; i++ ) {
	    pthread_join( tid[i], NULL );
	}
	
	printf("number = %d\n", number);
	
}
