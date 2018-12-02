#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


// printf("Start number = %d\n", number);
// https://stackoverflow.com/questions/3908031/how-to-multithread-c-code
//  gcc -pthread multithreading.c -o multithreading.o

void *get_result(void *param)
{
	pthread_t pthread_self(void);
	pid_t getpid(void);
	int *n = (int *)param;

	*n = (*n) * (*n) * (*n);

	//pid_t tid = syscall(SYS_gettid);

	printf("Thread ID: %lu\tResult = %d\n", pthread_self(), *n);
	
	return NULL;
}

int main()
{
  // Read how many numbers to ^3 and sum?
	int ntimes, i;	
	
	printf("How many numbers?\n");
	scanf("%d", &ntimes);

	pthread_t *tid = malloc( ntimes * sizeof(pthread_t) );
	int *results = malloc( ntimes * sizeof(int) );

	for( i = 0; i < ntimes; i++ ) {	
		printf("Write number: \n");
		scanf("%d", &results[i]);
	}

	for( i = 0; i < ntimes; i++ ) {	
		pthread_create(&tid[i], NULL, get_result, &results[i] );	
	}

	printf("End of numbers\n");

	//checking if the operation has ended

	for( i = 0; i < ntimes; i++ ) {
		pthread_join( tid[i], NULL );

		if ( tid[i] != 0 ) {
		//printf("Thread joined %d\n", tid[i]);
		}
	}

	int sum = 0;	

	// loop (for) over all numbers in *results and sum them.

	for( i = 0; i < ntimes; i++) {
		sum+=results[i];
	}

	printf("Sum = %d\tPID: %d\n", sum, getpid());	

return 0;
}
