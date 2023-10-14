#include "shell.h"

/**
 * replace_variable - Replaces a specific variable with its value.
 * @input: String to be modified.
 * @variable: Variable to be replaced.
 * @replacement: Replacement value for the variable.
 * Return: Modified string with the variable replaced.
 */
char *replace_variable(char *input, char *variable, char *replacement)
{
	char *pos;
	char *new_str;
	int input_len, variable_len, replacement_len;

	pos = strstr(input, variable);
	if (!pos)
		return (input);

	input_len = strlen(input);
	variable_len = strlen(variable);
	replacement_len = strlen(replacement);
	new_str = malloc(input_len - variable_len + replacement_len + 1);

	if (!new_str)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	strncpy(new_str, input, pos - input);
	strcpy(new_str + (pos - input), replacement);
	strcpy(new_str + (pos - input) + replacement_len, pos + variable_len);

	return (new_str);
}

/**
 * handle_replacements - Handles special replacements like $? and $$.
 * @input: String that may contain variables to be replaced.
 * @shell: Global shell state variable.
 * Return: Modified string with special variables replaced.
 */
char *handle_replacements(char *input, ShellState *shell)
{
	char last_exit_str[12];
	char pid_str[12];
	char *path_val;
	char *result = input;
	char *temp;

	sprintf(last_exit_str, "%d", shell->last_exit_status);
	temp = replace_variable(result, "$?", last_exit_str);
	if (result != temp && result != input)
		free(result);
	result = temp;

	sprintf(pid_str, "%d", getpid());
	temp = replace_variable(result, "$$", pid_str);
	if (result != temp && result != input)
		free(result);
	result = temp;

	path_val = getenv("PATH");
	if (path_val)
	{
		temp = replace_variable(result, "$PATH", path_val);
		if (result != temp && result != input)
			free(result);
		result = temp;
	}

	return (result);
}

