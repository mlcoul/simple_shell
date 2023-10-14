#include <stdio.h>
#include <stdlib.h>

/**
 * handle_setenv - Handles the setenv builtin command.
 * @args: Arguments given by the user.
 * Return: 1 if the shell should continue running, 0 if it should terminate.
 */
int handle_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: Argument required\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("Error setting environment variable");
	}
	return (1);
}

/**
 * handle_unsetenv - Handles the unsetenv builtin command.
 * @args: Arguments given by the user.
 * Return: 1 if the shell should continue running, 0 if it should terminate.
 */
int handle_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Argument required\n");
		return (1);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("Error unsetting environment variable");
	}
	return (1);
}

