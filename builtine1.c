#include "shell.h"

/**
 * _myhistory - displ the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Struc containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	prt_list(info->history);
	return (0);
}

/**
 * unst_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unst_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchars(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node_index(&(info->alias),
		get_nodeIndex(info->alias, node_str_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * st_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int st_alias(info_t *info, char *str)
{
	char *p;

	p = _strchars(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unst_alias(info, str));

	unst_alias(info, str);
	return (ad_nodes_end(&(info->alias), str, 0) == NULL);
}

/**
 * prt_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int prt_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchars(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			prt_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchars(info->argv[i], '=');
		if (p)
			st_alias(info, info->argv[i]);
		else
			prt_alias(node_str_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
