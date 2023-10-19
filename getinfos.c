#include "shell.h"

/**
 * clear_infos - initializes info_t struct
 * @info: struct address
 */
void clear_infos(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_infos - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_infos(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdups(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_aliass(info);
		replace_var(info);
	}
}

/**
 * free_infos - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_infos(info_t *info, int all)
{
	ffreee(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freee_list(&(info->env));
		if (info->history)
			freee_list(&(info->history));
		if (info->alias)
			freee_list(&(info->alias));
		ffreee(info->environ);
			info->environ = NULL;
		bfreee((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
