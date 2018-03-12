#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <stdbool.h>

#define BUFFER 256;

typedef struct {
	char name[256];
	int priority;
	int pid;
	//proc process;
	struct node* next;
} proc;

typedef struct node {
	proc process;
	struct node* next;
}queue;

queue* head =  NULL;

void push(proc process)
{
	queue *node1;
	node1 = malloc(sizeof(node_t));
	node1->process = process;
	node1->next = head;
	head = node1;
}
int main (void)
{
	FILE *fs = fopen("processes.txt", "r");
	char lines[256];
	while (fgets(lines, sizeof lines, fs) != NULL)
  	{
		proc data;
		char *var;
		char priority_t[256];
		char pid_t[256];
		char runtime_t[256];
		var = strtok(lines, ", ");
		int i = 0;
		while (parse != NULL)
		{
			if (i == 0)
			{	
				strcpy(data.name, var);
			}
			else if (i == 1)
			{	
				strcpy(priority_t, var);

			}
			else if (i == 2)
	
			{
				strcpy(pid_t, var);

			}
			else if (i == 3)

			{var
				strcpy(runtime_t, var);
			}
			i++;
			var = strtok(NULL, ", ");
		}
		data.priority = atoi(priority_t);
		data.pid = atoi(pid_t);
		data.runtime = atoi(runtime_t);
		push(data);
	}
	queue * current = head;

    	while (current != NULL)
 	{
        printf("%s\t" ,current->process.name);
	printf("%d\t" ,current->process.priority);
	printf("%d\t" ,current->process.pid);
	printf("%d\n" ,current->process.runtime);
        current = current->next;
	}
}
