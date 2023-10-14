#include "shell.h"

/**
 * handle_file_input - Executes commands from a given file.
 * @filename: Name of the file.
 * @shell: Pointer to the shell state structure.
 *
 * Return: 0 on success, else a failure status.
 */
int handle_file_input(char *filename, ShellState *shell)
{
	FILE *file;
	char command[120];
	char *modified_command;

	file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}

	while (fgets(command, sizeof(command), file))
	{
		strip_comments(command);
		modified_command = handle_replacements(command, shell);
		exec_command(modified_command, shell);
		if (modified_command != command)
			free(modified_command);
	}

	fclose(file);
	return (0);
}

/**
 * interactive_mode - Handles the shell's interactive mode.
 * @shell: Pointer to the shell state structure.
 */
void interactive_mode(ShellState *shell)
{
	char command[120];
	char *modified_command;

	while (1)
	{
		disp_prompt();
		read_cmd(command, sizeof(command));
		strip_comments(command);
		modified_command = handle_replacements(command, shell);
		exec_command(modified_command, shell);
		if (modified_command != command)
			free(modified_command);
	}
}

/**
 * main - Entry point for the custom shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: Always returns 0.
 */
int main(int argc, char **argv)
{
	ShellState shell;

	/* Initialize the shell state */
	init_alias_list(&shell);
	shell.last_exit_status = 0;

	if (argc > 1)
	{
		handle_file_input(argv[1], &shell);
		free_aliases(&shell);
		return (0);
	}

	interactive_mode(&shell);

	/* Free resources */
	free_aliases(&shell);
	return (0);
}

