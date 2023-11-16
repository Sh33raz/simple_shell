#include "shell.h"
/**
 * a_unset - unsets alias
 * @h: struct
 * @s: string
 * Return: 0 or 1
 */
int a_unset(me_t *h, char *s)
{
	char *p, c;
	int ret;

	p = _chara_(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rm_nodes_(&(h->aliaz),
		nodeget(h->aliaz, node_starts_(h->aliaz, s, -1)));
	*p = c;
	return (ret);
}

/**
 * a_set - sets alias
 * @h: struct
 * @s: string
 * Return: 0 or 1
 */
int a_set(me_t *h, char *s)
{
	char *p;

	p = _chara_(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (a_unset(h, s));

	a_unset(h, s);
	return (nodeends_(&(h->aliaz), s, 0) == NULL);
}

/**
 * palias - prints alias
 * @node: node
 * Return: 0 or 1
 */
int palias(list_me *node)
{
	char *p = NULL, *y = NULL;

	if (node)
	{
		p = _chara_(node->s, '=');
		for (y = node->s; y <= p; y++)
			_putchar_(*y);
		_putchar_('\'');
		_puts_(p + 1);
		_puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_me - mimics alias
 * @h: Struct
 * Return: Always 0
 */
int alias_me(me_t *h)
{
	int i = 0;
	char *p = NULL;
	list_me *node = NULL;

	if (h->arguc == 1)
	{
		node = h->aliaz;
		while (node)
		{
			palias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; h->arguv[i]; i++)
	{
		p = _chara_(h->arguv[i], '=');
		if (p)
			a_set(h, h->arguv[i]);
		else
			palias(node_starts_(h->aliaz, h->arguv[i], '='));
	}

	return (0);
}
