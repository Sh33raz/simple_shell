#include "shell.h"

/**
 * main - entry
 * @ac: counter
 * @av: vector
 * Return: 0 or 1
 */
int main(int ac, char **av)
{
	me_t h[] = { _INFO };
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
				_errputs(av[0]);
				_errputs(": 0: CAN NOT OPEN! ");
				_errputs(av[1]);
				_errputchar('\n');
				_errputchar(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		h->refd = fd;
	}
	_pplate(h);
	re_history(h);
	hsh(h, av);
	return (EXIT_SUCCESS);
}
