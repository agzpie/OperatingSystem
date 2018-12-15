// program gdzie jest proces macierzysty i duzo potomnych

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void procStatus(int nazwaPID) {
	printf("Proces nr P%d\t o PID: %d\tuśpiony\n", nazwaPID, getpid());
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

void createProcesses(int n) {
	singleChild(0);

	for (int i = 1; i <= n; i++) {
		singleChild(i);
	}


}

int main() {
	int n;
	printf("Podaj liczbe: ");
	scanf("%d", &n);
	createProcesses(n);

	return 0;

}
