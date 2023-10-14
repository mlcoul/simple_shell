#include "shell.h"

/**
 * mo_strsep - Similar function to strsep in the C library.
 * @stringp: The string to extract tokens from.
 * @delim: The delimiter for tokenizing.
 *
 * Return: The next token.
 */
char *mo_strsep(char **stringp, const char *delim)
{
	char *token_start;
	char *p;

	if (!stringp || !*stringp)
		return (NULL);

	token_start = *stringp;
	p = strstr(token_start, delim);

	if (p)
	{
		*p = '\0';
		*stringp = p + 1;  /* Move past the delimiter */
	}
	else
		*stringp = NULL;

	return (token_start);
}

/**
 * mo_tokenize - Tokenizes a string based on spaces.
 * @command: The command to tokenize.
 *
 * Return: A NULL-terminated array of pointers pointing to each token.
 */
char **mo_tokenize(char *command)
{
	char *token = NULL;
	size_t token_count = 0;
	char **tokens = malloc(sizeof(char *));  /* Start with a small allocation */

	if (!tokens)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	token = mo_strsep(&command, " ");
	while (token)
	{
		tokens[token_count++] = token;

		/* Reallocate memory for the new token */
		tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
		if (!tokens)
		{
			perror("Memory reallocation error");
			exit(EXIT_FAILURE);
		}

		token = mo_strsep(&command, " ");
	}
	tokens[token_count] = NULL;  /* Null-terminate the array */

	return (tokens);
}

