#include "shell.h"

/**
 * hsh_ - main
 * @h: parameters
 * @argv: arguments
 * Return: 0 or 1
 */
int hsh(me_t *h, char **argv)
{
	ssize_t r = 0;
	int ret = 0;

	while (r != -1 && ret != -2)
	{
		clear_me(h);
		if (me_int(h))
			_puts_("$ ");
		_errputchar(-1);
		r = _nputget(h);
		if (r != -1)
		{
			set_me(h, argv);
			ret = find_blt(h);
			if (ret == -1)
				find_words(h);
		}
		else if (me_int(h))
			_putchar_('\n');
		free_me(h, 0);
	}
	wr_history(h);
	free_me(h, 1);
	if (!me_int(h) && h->stats)
		exit(h->stats);
	if (ret == -2)
	{
		if (h->er_num == -1)
			exit(h->stats);
		exit(h->er_num);
	}
	return (ret);
}

/**
 * find_blt - builtin command
 * @h: parameters
 * Return: 0 if succes else if else
 */
int find_blt(me_t *h)
{
	int i, ret = -1;
	built_me builtintbl[] = {
		{"exit", exit_me},
		{"env", env_me},
		{"help", help_me},
		{"history", hist_me},
		{"setenv", setenv_me},
		{"unsetenv", unsetenv_me},
		{"cd", cd_me},
		{"alias", alias_me},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].t; i++)
		if (_cmp_(h->arguv[0], builtintbl[i].t) == 0)
		{
			h->line_count++;
			ret = builtintbl[i].f(h);
			break;
		}
	return (ret);
}

/**
 * find_words - command
 * @h: parameter
 * Return: void
 */
void find_words(me_t *h)
{
	char *pant = NULL;
	int i, j;

	h->pant = h->arguv[0];
	if (h->line_flag == 1)
	{
		h->line_count++;
		h->line_flag = 0;
	}
	for (i = 0, j = 0; h->argu[i]; i++)
		if (!dilem(h->argu[i], " \t\n"))
			j++;
	if (!j)
		return;

	pant = path_finder(h, envget(h, "PATH="), h->arguv[0]);
	if (pant)
	{
		h->pant = pant;
		fork_words(h);
	}
	else
	{
		if ((me_int(h) || envget(h, "PATH=")
			|| h->arguv[0][0] == '/') && is_words(h, h->arguv[0]))
			fork_words(h);
		else if (*(h->argu) != '\n')
		{
			h->stats = 127;
			print_errs(h, "NOT FOUND 404 !!\n");
		}
	}
}

/**
 * fork_cmd - forks cmd
 * @h: struct
 */
void fork_cmd(me_t *h)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		print_errs("ERROR!!");
		return;
	}
	if (child == 0)
	{
		if (execve(h->pant, h->arguv, _environget(h)) == -1)
		{
			befree(h, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(h->stats));
		if (WIFEXITED(h->stats))
		{
			h->stats = WEXITSTATUS(h->stats);
			if (h->stats == 126)
				print_errs(h, "Permission denied\n");
		}
	}
}
