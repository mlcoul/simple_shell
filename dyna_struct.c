#include "shell.h"
#include <stdlib.h>

/**
 * create_command - Allocates and initializes a command structure.
 * @separator: Character separating commands.
 * @command: Array of pointers, including the command and its tokens.
 *
 * Return: Pointer to new command structure, or NULL on failure.
 */
command_t *create_command(char separator, char **command)
{
	command_t *ret;

	ret = malloc(sizeof(command_t));
	if (!ret)
		return (NULL);

	ret->separator = separator;
	ret->command = command;
	/* By default, the previous command is valid */
	ret->prev_valid = 1;
	ret->next = NULL;
	return (ret);
}

/**
 * free_command_queue - Frees a queue of commands.
 * @q: Pointer to the queue.
 */
void free_command_queue(queue_t *q)
{
	command_t *temp;

	if (!q)
		return;

	temp = q->front;
	while (temp)
	{
		free_command(temp);
		temp = temp->next;
	}
	q->front = q->rear = NULL;
	free(q);
}

/**
 * free_token_list - Frees an array of tokens.
 * @tokens: 2D array of tokens.
 */
void free_token_list(char **tokens)
{
	int i = 0;

	if (!tokens)
		return;

	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/**
 * free_command - Frees a command and its associated token list.
 * @command: Pointer to the command to free.
 */
void free_command(command_t *command)
{
	if (command)
	{
		free_token_list(command->command);
		free(command);
	}
}

