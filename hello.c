#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void procStatus() {
	printf("PID[%d] (PPID[%d])\n", getpid(), getppid());
	fflush(NULL);
}

void singleChild() {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus();
		exit(0);
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
		
		for (int i = 0; i < 3; i++) {
			singleChild();
		}

		exit(0);
	}
	else {
		wait(NULL);
	}
}

void proces3() {
	pid_t pid = fork();
	if (pid == 0) {
		procStatus();
		pid_t pid2 = fork();
		if (pid2 == 0) {
			procStatus();
			singleChild();
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

int main() {	

	procStatus();
	proces1();
	proces2();
	proces1();
	proces3();

	return 0;
}

