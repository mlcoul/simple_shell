#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * create_queue - Initializes an empty queue.
 *
 * Return: Pointer to the newly created queue or NULL on failure.
 */
queue_t *create_queue(void)
{
	queue_t *q = malloc(sizeof(queue_t));

	if (!q)
		return (NULL);

	q->front = NULL;
	q->rear = NULL;
	return (q);
}

/**
 * enqueue - Inserts a new command into the queue.
 * @q: Pointer to the target queue.
 * @separator: Character used to separate commands.
 * @command: Pointer to the start of the command string.
 *
 * Return: 1 if successful, 0 if an error occurs.
 */
int enqueue(queue_t *q, char separator, char **command)
{
	command_t *new_node = create_command(separator, command);

	if (!new_node)
		return (0);

	if (!q->rear)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
	return (1);
}

/**
 * dequeue - Removes the first command from the queue after it's executed.
 * @q: Pointer to the target queue.
 *
 * Return: Pointer to the command that was removed or NULL if empty.
 */
command_t *dequeue(queue_t *q)
{
	command_t *old_node;

	if (!q->front)
		return (NULL);

	old_node = q->front;
	q->front = q->front->next;

	if (!q->front)
		q->rear = NULL;

	return (old_node);
}

