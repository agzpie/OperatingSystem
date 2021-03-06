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

int proces2() {
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

	return pid;
}

int proces3() {
	return singleChild(4);
}

int proces4() {
	pid_t pid = fork();

	if (pid == 0) {
		int childrenP5[2];
		for (int i = 0; i <= 1; i++) {
			childrenP5[i] = singleChild(i+8);
		}

		procWithChildrenStatus(5, childrenP5, 2);
		exit(0);
	}
	else {
		wait(NULL);
	}

	return pid;
}


int main() {
	int childrenP1[4];
	childrenP1[0] = proces1();
	childrenP1[1] = proces2();
	childrenP1[2] = proces3();
	childrenP1[3] = proces4();

	procWithChildrenStatus(1, childrenP1, 4);

	return 0;

}








