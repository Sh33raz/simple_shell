#include "shell.h"

/**
 * exit_me - exit
 * @h: Struct
 *  Return: exit
 */
int exit_me(me_t *h)
{
	int x;

	if (h->arguv[1])
	{
		x = _eratotin(h->arguv[1]);
		if (x == -1)
		{
			h->stats = 2;
			print_errs(h, "NOT a number: ");
			_errputs(h->arguv[1]);
			_errputchar('\n');
			return (1);
		}
		h->er_num = _eratotin(h->arguv[1]);
		return (-2);
	}
	h->er_num = -1;
	return (-2);
}

/**
 * cd_me - change cd
 * @h: Struct
 * Return: Always 0
 */
int cd_me(me_t *h)
{
	char *s, *d, buf[1024];
	int ret;

	s = getcwd(buf, 1024);
	if (!s)
		_puts_("ERROR!!\n");
	if (!h->arguv[1])
	{
		d = envget(h, "HOME=");
		if (!d)
			ret = chdir((d = envget(h, "PWD=")) ? d : "/");
		else
			ret = chdir(d);
	}
	else if (_cmp_(h->arguv[1], "-") == 0)
	{
		if (!envget(h, "OLD PWD="))
		{
			_puts_(s);
			_putchar_('\n');
			return (1);
		}
		_puts_(envget(h, "OLD PWD=")), _putchar_('\n');
		ret = chdir((d = envget(h, "OLD PWD=")) ? d : "/");
	}
	else
		ret = chdir(h->arguv[1]);
	if (ret == -1)
	{
		print_errs(h, "can't CD to ");
		_errputs(h->arguv[1]), _errputchar('\n');
	}
	else
	{
		_setenv(h, "OLD PWD", envget(h, "PWD="));
		_setenv(h, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * help_me - changes the current directory of the process
 * @h: Struct
 *  Return: Always 0
 */
int help_me(me_t *h)
{
	char **a;

	a = h->arguv;
	_puts_("WORKS \n");
	if (0)
		_puts_(*a);
	return (0);
}

/**
 * hist_me - history list
 * @h: Struct
 *  Return: Always 0
 */
int hist_me(me_t *h)
{
	plist(h->histo);
	return (0);
}
