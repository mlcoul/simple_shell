#include "shell.h"
#include <string.h>

/**
 * execute_single_command - Executes a single command.
 * @command: The command string to execute.
 *
 * Return: Execution status.
 */
int execute_single_command(char *command, ShellState *shell)

{
	char **args;
	pid_t child_pid;
	int status = 0;

	/* Tokenize the command */
	args = mo_tokenize(command);

	/* Handle "exit" command */
	if (strcmp(args[0], "exit") == 0)
		handle_exit(args,shell);

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork");
		return (EXIT_FAILURE);
	}

	if (child_pid == 0)  /* Child process */
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Child process");
			exit(EXIT_FAILURE);
		}
	}
	else  /* Parent process */
	{
		wait(&status);
	}

	return (status);
}

