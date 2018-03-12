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
	
	const char *command = "./process";
	int status;
	pid_t pid;

	pid = fork();
	if (pid == 0) { 
		execv(command, argv);
		exit(0);
		_exit(EXIT_FAILURE);
	} else if (pid < 0) {
		status = -1;
	} else { 
		sleep(5);
		
		kill(pid, SIGTSTP);
		
		sleep(10);
		kill(pid, SIGCONT);
		waitpid(pid, &status, 0);
		
		if (status == 0) {
			exit(0);
		}
		return status;
	}
}
