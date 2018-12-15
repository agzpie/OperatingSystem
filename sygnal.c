// program gdzie jest proces macierzysty i duzo potomnych

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

pid_t pid = -1; //global

void procStatus(int nazwaPID) {
	printf("Proces nr P%d\t o PID: %d\tuśpiony\n", nazwaPID, getpid());
	fflush(NULL); 
}

void kill_child(int sig) {
	kill(pid,SIGKILL);
}

int singleChild(int nazwaPID) {
	signal(SIGALRM,(void (*)(int))kill_child);
	pid_t pid = fork();
	if (pid == 0) {
		printf("Starting child process P%d...\n", nazwaPID);
		sleep(10);
		procStatus(nazwaPID);
		printf("Process ended\n");
		exit(0);
	}
	else if (pid == -1) {
		printf("Blad funkcji fork\n");
		exit(1);
	}
	else {
		alarm(10);
		printf("Parent is killing...");
		wait(NULL);
	}

	return pid;
}

int proces1() {
	return singleChild(2);
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
