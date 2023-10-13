#include "shell.h"

/**
 * read_cmd - Reads a command from the standard input.
 * @command: A pointer to the buffer where the command will be stored.
 * @size: The maximum number of characters to be read.
 *
 * Description: If an error occurs or the end of the file is reached,
 * the function will print a message and then exit.
 */
void read_cmd(char *command, size_t size)

{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			mo_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			mo_print("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}

