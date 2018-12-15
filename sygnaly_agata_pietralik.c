#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void controlC(int number) {
	if (getchar() == '1') {
		exit(0);
	}
	printf("control + c\t\t signal: SIGINT\t\t number: 2\n");
}

void controlZ(int number) {
		if (getchar() == '1') {
		exit(0);
	}
	printf("control + z\t\t signal: SIGSTP\t\t number: 18, 20, 24\n");
}

void controlBackslash(int number) {
		if (getchar() == '1') {
		exit(0);
	}
	printf("control + backslash\t signal: SIGQUIT\t\t number: 3\n");
}

int main() {

	signal(SIGTSTP, controlZ);

	signal(SIGINT, controlC);

	signal(SIGQUIT, controlBackslash);

	if (getchar() == '1') {
		exit(0);
	}

	while( 1 ) {}

	return 0;
}
