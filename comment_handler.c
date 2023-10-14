#include "shell.h"

/**
 * strip_comments - Remove comments starting with '#' from a command.
 * @cmd: The command string to be processed.
 */
void strip_comments(char *cmd)
{
	char *hash_position;

	hash_position = strchr(cmd, '#');
	if (hash_position)
		*hash_position = '\0';
}

