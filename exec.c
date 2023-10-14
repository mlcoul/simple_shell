#include "shell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * handle_exit - Handles the "exit" command.
 * @args: The arguments.
 * @shell: The shell state.
 */
void handle_exit(char **args, ShellState *shell)
{
	if (args[1])
	{
		shell->last_exit_status = atoi(args[1]);
		exit(shell->last_exit_status);
	}
	else
	{
		shell->last_exit_status = EXIT_SUCCESS;
		exit(EXIT_SUCCESS);
	}
}

/**
 * exec_command - Executes a single command read from the user.
 * @command: The command string to execute.
 * @shell: The shell state.
 * Return: Exit status of the executed command.
 */
int exec_command(char *command, ShellState *shell)
{
	char **args;
	pid_t child_pid;
	int status;

	/* Tokenize the command */
	args = mo_tokenize(command);

	/* Check for "exit" command */
	if (strcmp(args[0], "exit") == 0)
		handle_exit(args, shell);

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			perror("Child process");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
		shell->last_exit_status = WEXITSTATUS(status);
	}

	free(args);
	return (shell->last_exit_status);
}

/**
 * execute_commands - Tokenizes commands separated by logical operators and
 * executes them.
 * @line: The input line containing one or more commands.
 * @shell: The shell state.
 */
void execute_commands(char *line, ShellState *shell)
{
	char **commands;
	char **operators;
	int i = 0;

	commands = split_commands(line);
	operators = get_operators(line);

	while (commands[i])
	{
		if (operators[i] && strcmp(operators[i], "&&") == 0)
		{
			if (exec_command(commands[i], shell) != 0)
				break;
		}
		else if (operators[i] && strcmp(operators[i], "||") == 0)
		{
			if (exec_command(commands[i], shell) == 0)
				break;
		}
		else
		{
			exec_command(commands[i], shell);
		}
		i++;
	}

	free(commands);
	free(operators);
}

