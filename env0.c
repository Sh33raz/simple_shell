#include "shell.h"

/**
 * env_me - current environment
 * @h: Struct
 * Return: Always 0
 */
int env_me(me_t *h)
{
	pliststr_(h->_envenv);
	return (0);
}

/**
 * envget - gets environ
 * @h: Struct
 * @n: name
 * Return: value
 */
char *envget(me_t *h, const char *n)
{
	list_me *node = h->_envenv;
	char *p;

	while (node)
	{
		p = _starts_(node->s, n);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setenv_me - Initialize environment
 * @h: Struct
 * Return: Always 0
 */
int setenv_me(me_t *h)
{
	if (h->arguc != 3)
	{
		_errputs("ERROR\n");
		return (1);
	}
	if (_setenv(h, h->arguv[1], h->arguv[2]))
		return (0);
	return (1);
}

/**
 * unsetenv_me - Remove environment
 * @h: Struct
 * Return: Always 0
 */
int unsetenv_me(me_t *h)
{
	int i;

	if (h->arguc == 1)
	{
		_errputs("Few arguements.\n");
		return (1);
	}
	for (i = 1; i <= h->arguc; i++)
		_unsetenv(h, h->arguv[i]);

	return (0);
}
