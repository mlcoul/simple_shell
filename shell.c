#include "shell.h"

/**
 * main - entry first point
 * @ac: arg count to arg
 * @av: arg vector to vec
 *
 * Return: 0 on suc, 1 on err
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputss(av[0]);
				_eputss(": 0: Can't open ");
				_eputss(av[1]);
				_eputchara('\n');
				_eputchara(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_hist(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
