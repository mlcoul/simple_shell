#include "shell.h"

/**
 * cd_home - Change to the home directory.
 * Return: 0 on success, 1 on failure.
 */
int cd_home(void)
{
	char *home = getenv("HOME");

	if (home == NULL)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return (1);
	}

	if (chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * cd_previous - Change to the previous directory.
 * Return: 0 on success, 1 on failure.
 */
int cd_previous(void)
{
	if (chdir(getenv("OLDPWD")) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * handle_cd - Change directories.
 * @args: Arguments provided by the user.
 * Return: 0 on success, 1 on failure.
 */
int handle_cd(char **args)
{
	if (args[1] == NULL)
	{
		if (cd_home() != 0)
			return (1);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (cd_previous() != 0)
			return (1);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}

	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(NULL, 0), 1);

	return (0);
}

