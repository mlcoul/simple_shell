exec.c
#include "shell.h"

/**
 * exec_command - Executes a given command.
 * @command: The command string to execute.*
 * Description: This function forks the current process and tries
 * to execute the given command in the child process.
 */
void exec_command(const char *command)
{
	pid_t child_pid;
	char *args[128];
	int arg_count = 0;
	char *token;

	child_pid = fork();
	if (child_pid == -1)
	{
		mo_print("Error forking process.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		token = strtok((char *)command, " ");
		while (token != NULL && arg_count < 127)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;
		execvp(args[0], args);
		mo_print("Error executing command.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

