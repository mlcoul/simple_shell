#include "main.h"

/**
 *_isupper - function that check if uppercase
 *@c: char to be checked
 *Return: Always 1 succes and 0 failed
 */
int _isupper(int c)
{
	if (c >= 65 && c <= 90)
	{
	return (1);
	}
	return (0);
}
