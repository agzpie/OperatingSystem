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
	singleChild();
}

void proces2() {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus();
		singleChild();

		pid_t pid2 = fork();
		if (pid2 == 0) {
			procStatus();
			singleChild();

			exit(0);
		}
		else {+
			wait(NULL);
		}
		exit(0);
	}
	else {
		wait(NULL);
	}
}

void proces3() {
	singleChild();
}

void proces4() {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus();
		
		for (int i = 0; i < 2; i++) {
			singleChild();
		}

		exit(0);
	}
	else {
		wait(NULL);
	}
}


int main() {

	int nazwaPID = 0;
		
	procStatus();
	proces1();
	proces2();
	proces3();
	proces4();

	return 0;

}








