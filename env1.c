#include "shell.h"

/**
 * _pplate - populates env
 * @h: Struct
 * Return: Always 0
 */
int _pplate(me_t *h)
{
	list_me *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		nodeends_(&node, environ[i], 0);
	h->_envenv = node;
	return (0);
}

/**
 * _environget - returns environ
 * @h: Struct
 * Return: Always 0
 */
char **_environget(me_t *h)
{
	if (!h->_envrn || h->env_cng)
	{
		h->_envrn = s_lists(h->_envenv);
		h->env_cng = 0;
	}

	return (h->_envrn);
}

/**
 * _unsetenv - Remove environment
 * @h: Struct
 * @v: var
 * Return: 1 or 0
 */
int _unsetenv(me_t *h, char *v)
{
	list_me *node = h->_envenv;
	size_t i = 0;
	char *p;

	if (!node || !v)
		return (0);

	while (node)
	{
		p = _starts_(node->s, v);
		if (p && *p == '=')
		{
			h->env_cng = rm_nodes_(&(h->_envenv), i);
			i = 0;
			node = h->_envenv;
			continue;
		}
		node = node->next;
		i++;
	}
	return (h->env_cng);
}

/**
 * _setenv - Initialize environment
 * @h: Struct
 * @v: var
 * @x: value
 * Return: Always 0
 */
int _setenv(me_t *h, char *v, char *x)
{
	char *buf = NULL;
	list_me *node;
	char *p;

	if (!v || !x)
		return (0);

	buf = malloc(_len_(v) + _len_(x) + 2);
	if (!buf)
		return (1);
	_cpy_(buf, v);
	_cat_(buf, "=");
	_cat_(buf, x);
	node = h->_envenv;
	while (node)
	{
		p = _starts_(node->s, v);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buf;
			h->env_cng = 1;
			return (0);
		}
		node = node->next;
	}
	nodeends_(&(h->_envenv), buf, 0);
	free(buf);
	h->env_cng = 1;
	return (0);
}
