#include "shell.h"

/**
 * read_from_stream -  to read char
 * Helper function to read characters from the stream.
 * @lineptr: Pointer to the buffer where characters will be stored.
 * @buffer: Temporary buffer to hold stream data.
 * @n: Size of the buffer.
 * @stream: The input stream to read from (like stdin).
 * @count: Ptr to a var holding the number of characters in buffer.
 * Return: The nbr of char read, or -1 on failure.
 */

ssize_t read_from_stream(char **lineptr, char *buffer, size_t *n,
	FILE *stream, ssize_t *count)

{
	char *ptr = buffer;
	char *line = *lineptr;
	size_t len = 0;

	while (1)
	{
		if (*count == 0)
		{
			*count = read(fileno(stream), buffer, sizeof(buffer));
			if (*count == 0)
				return (len);   /* EOF */
			if (*count < 0)
				return (-1);   /* Error */
		}

		if (len + 1 >= *n)  /* Reallocate line buffer if needed */
		{
			*n += 120;
			*lineptr = realloc(*lineptr, *n);
			if (!*lineptr)
				return (-1);
			line = *lineptr + len;
		}

		*line++ = *ptr++;
		len++;
		(*count)--;

		if (line[-1] == '\n')
		{
			*line = '\0';
			return (len);
		}
	}
}

/**
 * mo_getline - Reads an entire line from stream.
 * @lineptr: Pointer to buffer that the line will be stored.
 * @n: Size of the buffer.
 * @stream: The input stream to read from (like stdin).
 * Description: This function reads an entire line from the specified
 * stream, storing it in the buffer. If the buffer is not big enough,
 * it will be reallocated.
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t mo_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[120];
	static ssize_t count;

	if (!lineptr || !n || !stream)
		return (-1);

	if (!*lineptr)  /* If lineptr points to NULL, allocate memory */
	{
		*lineptr = malloc(120);
		if (!*lineptr)
			return (-1);
		*n = 120;
	}

	return (read_from_stream(lineptr, buffer, n, stream, &count));
}

