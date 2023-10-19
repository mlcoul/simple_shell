#include "shell.h"

/**
 * interactive - return true if is interactive mode
 * @info: structure address
 *
 * Return: 1 if interactive , 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimit - checks if char is a delimeter
 * @c: the char to check
 * @delim: the delimeter str
 * Return: 1 if true, 0 if false
 */
int is_delimit(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalphas - checks for alphabetic char
 *@c: The charar to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalphas(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoie - converts a str to an int
 *@s: the string to be converted
 *Return: 0 if no numbers in str, converted number otherwise
 */

int _atoie(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

