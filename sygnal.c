// program gdzie jest proces macierzysty i duzo potomnych i sa wysylane sygnaly

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void procStatus(int processNumber) {
	printf("Process nr P%d\t with PID: %d\tand PPID: %d\tis sleeping\n", processNumber, getpid(), getppid());
	fflush(NULL); 
}

void kill_child(int sig) {
	pid_t pid = -1; 
	kill(pid,SIGTERM);
}

	//signal(SIGALRM,(void (*)(int))kill_child);

int main() {
	int n;
	
	printf("PID: %d\n", getpid());
	printf("Podaj liczbe: ");
	scanf("%d", &n);
	pid_t tab[n];
	time_t t;
	srand((unsigned) time(&t));
	
	for (int i = 1; i <= n; i++) {
		pid_t pid = fork();
		tab[i-1] = pid;

		if (pid == 0) {
			int random = rand() % 10;

			printf("Starting child process P%d...\n", i);
			procStatus(i);
			sleep(random);
			printf("Awakening child process P%d\twith pid:\t%d\n", i,  getpid());
			exit(0);
		}
		else if (pid == -1) {
			printf("Blad funkcji fork\n");
			exit(1);
		}
	}
	
	pid_t pidFirst = wait(NULL); //first child to finish

	for (int i = 1; i <= n; i++) {
		if (tab[i-1] != pidFirst) {
			printf("Exterminating child process with pid:\t%d\n", tab[i-1]);
			kill(tab[i-1], SIGTERM);
		}
	}

	return 0;
}
