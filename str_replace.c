#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * str_replace - Replaces all occurrences of a substring with another substring
 * @origin: The original string
 * @from: The substring to find
 * @to: The substring to replace with
 *
 * Return: The new string with all occurrences replaced
 */
char *str_replace(const char *origin, const char *from, const char *to)
{
	char *result, *ins, *tmp;
	size_t len_from, len_to, len_front, count;

	if (!origin || !from || !to)
		return (NULL);

	len_from = strlen(from);
	len_to = strlen(to);

	ins = strstr(origin, from);
	for (count = 0; ins; ++count)
	{
		ins = strstr(ins + len_from, from);
	}

	tmp = result = malloc(strlen(origin) + (len_to - len_from) * count + 1);

	if (!result)
		return (NULL);

	while (count--)
	{
		ins = strstr(origin, from);
		len_front = ins - origin;
		tmp = strncpy(tmp, origin, len_front) + len_front;
		tmp = strcpy(tmp, to) + len_to;
		origin += len_front + len_from;
	}
	strcpy(tmp, origin);
	return (result);
}

