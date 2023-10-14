#include "shell.h"

/**
 * replace_dollar_dollar - Replaces occurrences of $$ with the shell's PID.
 * @cmd: The command to process.
 * @shellState: The shell's state.
 * Return: The newly allocated string with replacements, or NULL on failure.
 */
char *replace_dollar_dollar(char **cmd, ShellState *shellState)
{
	char pid_str[12];
	(void) shellState;

	sprintf(pid_str, "%d", getpid());
	return (str_replace(*cmd, "$$", pid_str));
}

/**
 * replace_dollar_question - Replaces occurrences of $? with the last command's
 * exit status.
 * @cmd: The command to process.
 * @shellState: The shell's state.
 * Return: The newly allocated string with replacements, or NULL on failure.
 */
char *replace_dollar_question(char **cmd, ShellState *shellState)
{
	char status_str[12];

	sprintf(status_str, "%d", shellState->last_exit_status);
	return (str_replace(*cmd, "$?", status_str));
}

/**
 * process_variable_replacement
 * Processes variable replacement in the given command.
 * @cmd: The command to process.
 * @shellState: The shell's state.
 * Return: The newly allocated string after replacements, or NULL on failure.
 */
char *process_variable_replacement(char **cmd, ShellState *shellState)
{
	char *new_cmd = NULL;
	char *env_value;

	new_cmd = replace_dollar_dollar(cmd, shellState);
	if (new_cmd)
	{
		free(*cmd);
		*cmd = new_cmd;
	}

	new_cmd = replace_dollar_question(cmd, shellState);
	if (new_cmd)
	{
		free(*cmd);
		*cmd = new_cmd;
	}

	env_value = getenv("PATH");
	if (env_value)
	{
		new_cmd = str_replace(*cmd, "$PATH", env_value);
		if (new_cmd)
		{
			free(*cmd);
			*cmd = new_cmd;
		}
	}

	return (*cmd);
}

