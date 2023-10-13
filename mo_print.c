#include "shell.h"

/**
 * mo_print - Prints a message to the standard output.
 * @msg: The message to be printed.
 * Description: Uses the write function to display the provided message.
 */

void mo_print(const char *msg)
{
	write(STDOUT_FILENO, msg, strlen(msg));
}
