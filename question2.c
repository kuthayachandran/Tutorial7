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
	int runtime;
}proc;

typedef struct node {
	proc process;
	struct node* next;
}queue;

queue* head =  NULL;

void push (proc process)
{
queue *node1;
	node1 = malloc(sizeof(node_t));
	node1->process = process;
	node1->next = head;
	head = queue;
}

proc pop()
{
	proc *data = NULL;
	queue * node2 = NULL;
	node2 = (head)->next;
	data = &(head)->process;
	free(head);
	head = node2;
	return *data;
}
int delete_name(char *name)
{
	if (strcmp(head->process.name,name) == 0)
  	{
		queue *t = head;
		head = head->next;
		free(t);
		return 1;
	}
	queue *current = head->next;
	queue *previous = head;

	while (current != NULL && previous != NULL)
	{

		if (strcmp((current->process.name),name) == 0)
		{

			queue *t = current;
			previous->next = current->next;
			free(t);
			return 1;
		}
 
		previous = current;
		current = current->next;
	}
	return 0;
}

int delete_pid(int pid)
{
	queue *current = head;
	queue *previous = head;
	while (current != NULL && previous != NULL)
	{
		if (node->process.pid == pid)
		{
			queue *t = current;	
			previous->next = current->next;
			free(t);
			return 1;
		} 
		previous = current;
		current = current->next;
	}
	return 0;
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
			{
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
	delete_name("emacs");
	delete_pid(12235);
	queue * current = head;
  	while (current != NULL)
	{
    		proc t = pop();
       		printf("%s\t" ,t.name);
		printf("%d\t" ,t.priority);
		printf("%d\t" ,t.pid);
		printf("%d\n" ,t.runtime);
		current = current->next;

	}

}
