#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void procStatus(int nazwaPID) {
	printf("Nazwa procesu: P%d\t PID: %d\tPPID: %d\n", nazwaPID, getpid(), getppid());
	fflush(NULL); 
}

void procWithChildrenStatus(int nazwaPID, int children[], int numOfChildren) {
	procStatus(nazwaPID);;

	printf("Potomni P%d: ", nazwaPID);

	for (int i = 0; i < numOfChildren; i++) {
	
		printf("%d", children[i]);
		if (i != numOfChildren - 1 ) {
			printf(", ");
		}
	}

	printf("\n");
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

int proces1() {
	return singleChild(2);
}

void proces2() {
	int childrenP3[2];
	pid_t pid = fork();
	if (pid == 0) {
		
		childrenP3[0] = singleChild(6);

		pid_t pid2 = fork();
		if (pid2 == 0) {
			int childrenP7[1];
			
			childrenP7[0] = singleChild(10);

			procWithChildrenStatus(7, childrenP7, 1);

			exit(0);
		}
		else {
			childrenP3[1] = (int) pid2;
			wait(NULL);
		}
		
		procWithChildrenStatus(3, childrenP3, 2);
	
		exit(0);
	}
	else {
		wait(NULL);
	}
}

int proces3() {
	return singleChild(4);
}

void proces4() {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus(5);
		
		for (int i = 8; i <= 9; i++) {
			singleChild(i);
		}

		exit(0);
	}
	else {
		wait(NULL);
	}
}


int main() {
		
	procStatus(1);
	proces1();
	proces2();
	proces3();
	proces4();

	return 0;

}








