#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void procStatus(int nazwaPID) {
	printf("Nazwa procesu: P%d\t PID: %d\tPPID: %d\n", nazwaPID, getpid(), getppid());
	fflush(NULL);
}

void singleChild(int nazwaPID) {
	
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
}

void proces1() {
	singleChild(2);
}

void proces2() {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus(3);
		singleChild(6);

		pid_t pid2 = fork();
		if (pid2 == 0) {
			procStatus(7);
			singleChild(10);

			exit(0);
		}
		else {
			wait(NULL);
		}
		exit(0);
	}
	else {
		wait(NULL);
	}
}

void proces3() {
	singleChild(4);
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








