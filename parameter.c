#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void procStatus(int nazwaPID) {
	printf("Nazwa procesu: P%d\t PID: %d\tPPID: %d\n", nazwaPID, getpid(), getppid());
	fflush(NULL); 
}

int singleChild(int nazwaPID) {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus(nazwaPID);
		exit(0);
	}
	else if (pid == -1) {
		printf("Blad funkcji fork\n");
		exit(1);
	}
	else {
		wait(NULL);
	}

	return pid;
}

void howManyChildren() {
	int n;
	printf("How many processes to create?\n");
	scanf("%d", &n);

	for ( int i = 1; i <= n; i++ ) {
		singleChild(i);
	}
	return;
}

int main() {
	howManyChildren();

	return 0;
}








