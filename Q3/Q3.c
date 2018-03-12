#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SHELL "/bin/sh"

int main(int argc, char *argv[]) {
	int status;
	pid_t pid;
	const char *command = "./process";
	pid = fork();

	if (pid < 0) {
		} else if (pid == 0) {
		execv(command, argv);
		exit(0);
		_exit(EXIT_FAILURE);
	} else {
		sleep(5);
		kill(pid, SIGINT);
		if(wait(&status)){
			printf("Child terminated");
		}
	}
}
