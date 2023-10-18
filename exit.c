#include "shell.h"
#include <stdlib.h>

/**
 * exit_shell - Cleans up memory and exits the shell.
 * @his_q: The history queue.
 * @q: The main command queue.
 * @status: The status code to exit with.
 * @environ: The environment variables array.
 *
 * Description: Before exiting, this function saves the history
 *              to a file, then frees the command and history queues.
 */
void exit_shell(his_q_t *his_q, queue_t *q, int status, char **environ)
{
	write_queue_to_file(his_q, environ);
	free_command_queue(q);
	free_history_queue(his_q);
	exit(status);
}

