#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define SHELL "/bin/sh"

typedef struct {
	char name[256];
	int priority;
	int pid;
	int runtime;
} proc;

int MAX_BUFF_SIZE = 256;

typedef struct node {
	proc process;
	struct node *next;
} node_t;

node_t *queue;
proc tempProc;

void push(proc process) {
	node_t *current = queue; 
	while (current->next != NULL) {
		current = current->next;
	}
	
	current->next = (node_t *) malloc(sizeof(node_t));
	current->next->process = process;
	current->next->next = NULL; 
}

proc * delete_name(char *name) {
	node_t *current = queue->next;
	node_t *previous = queue;
	while (current != NULL) {

		tempProc = current->process;
		if (strcmp(tempProc.name, name) == 0) {
			node_t *deletedNode = current;
			previous->next = current->next;
			free(deletedNode);
			return &tempProc;
		}
		previous = current;
		current = current->next;
	}
	printf("process not found\n");
	return NULL;
}

proc * pop() {
	node_t * next_node = NULL;
	if (queue->next == NULL) {
		printf("in NULL");

		return NULL;
	}

	next_node = queue->next->next; 
	node_t * currentNode = queue->next;
	tempProc = currentNode->process;


	free(currentNode);
	queue->next = next_node;

	return &tempProc;
}
void printProc(proc *pro) {
	if (pro != NULL) {
		printf("Name: %s\nPriority: %d\npid: %d\nRuntime: %d\n\n", (pro->name),
				pro->priority, pro->pid, pro->runtime);
	}
}

void printList(node_t *list) {
	node_t * current = list;
	current = current->next;
	while (current != NULL) {
		tempProc = current->process;
		printProc(&tempProc); 
		current = current->next; 
	}
}

int main(int argc, char *argv[]) {
	
	queue = NULL;
	
	queue = malloc(sizeof(node_t));
	queue->next = NULL;


	proc tempProcess;

	FILE *fp = fopen("processes_q5.txt", "r");

	if (!fp) {
		printf("Error opening file");
		exit(EXIT_FAILURE);
	}

	size_t len = 0;
	ssize_t read;
	char *line = NULL;

	while ((read = getline(&line, &len, fp)) != -1) {
		
		char * tokens = NULL;
		tokens = strtok(line, ",\n");
		strcpy(tempProcess.name, tokens);
		tokens = strtok(NULL, ", \n");
		tempProcess.priority = atoi(tokens); 
		tokens = strtok(NULL, ", \n");
		tempProcess.pid = 0;
		tempProcess.runtime = atoi(tokens);
		push(tempProcess); 
	}
	
	fclose(fp);
	node_t * current = queue;
	
	current = current->next;
	while (current != NULL) {
		tempProcess = current->process; 
		if (tempProcess.priority == 0) { 
			const char *command = tempProcess.name;
			int status;
			pid_t pid;
			
			pid = fork();
			if (pid == 0) { 
				execv(command, argv);
				delete_name(tempProcess.name);
				execv("./process", argv);
				exit(0);
			} else if (pid < 0) { 
				status = -1;
			} else { 
				kill(pid, SIGINT);
				waitpid(pid, &status, 0);
				if (status == 0) { 
					tempProcess.pid = pid;
					printProc(&tempProcess);
					
					current = current->next;
				}
			}
		} else { 
			const char *command = tempProcess.name;
			int status;
			pid_t pid;
			
			pid = fork();
			if (pid == 0) { 
				execv(command, argv);
				exit(0);
			} else if (pid < 0) { 
				status = -1;
			} else { 
				sleep(tempProcess.runtime);
				
				kill(pid, SIGINT);
				
				waitpid(pid, &status, 0);
				if (status == 0) { 
					tempProcess.pid = pid;
					
					printProc(&tempProcess);
					
					current = current->next;
					pop(); 
				}
			}
		}
	}

	return 0;
}
