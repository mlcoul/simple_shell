#include "shell.h"

/**
 * _myenvi - print the current envir
 * @info: Struc containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenvi(info_t *info)
{
	prt_list_str(info->env);
	return (0);
}

/**
 * _getenvi - gets the value of an envir variable
 * @info: Struc containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenvi(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = st_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenvi - Initialize a new envir variable,
 *             or modify an existing one
 * @info: Struc containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenvi(info_t *info)
{
	if (info->argc != 3)
	{
		_eputss("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvi(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenvi - Remove an envir variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenvi(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputss("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenvir(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Struc containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		ad_nodes_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
