#include "shell.h"

/**
 * main - Starts our friendly shell CLI
 * @argc: Count of command-line arguments
 * @argv: Pointer to the array of command-line arguments
 *
 * Description: This program starts our friendly shell CLI.
 * Return: 0 for a successful start
 */
int
main(int argc, char **argv)
{
    /* We're not using argc here, so let's ignore it for now. */
	(void)argc;

    /* Start the shell and pass in the environment and program name. */
	return (start_shell(environ, argv[0]));
}

