#include "shell.h"

/**
 * main - Entry point for the custom shell program.
 * Description: Continuously prompts the user for commands, reads them,
 * and executes the commands.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char command[120];

	while (1)

	{
		disp_prompt();
		read_cmd(command, sizeof(command));
		exec_command(command);
	}

	return (0);
}

