#include "shell.h"

/**
 * l_lists - length of list
 * @h: head
 * Return: size
 */
size_t l_lists(const list_me *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * s_lists - array of strings
 * @h: head
 * Return: array of strings
 */
char **s_lists(list_me *h)
{
	list_me *node = h;
	size_t i = l_lists(h), j;
	char **ss;
	char *s;

	if (!h || !i)
		return (NULL);
	ss = malloc(sizeof(char *) * (i + 1));
	if (!ss)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_len_(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(ss[j]);
			free(ss);
			return (NULL);
		}

		s = _cpy_(s, node->s);
		ss[i] = s;
	}
	ss[i] = NULL;
	return (ss);
}

/**
 * plist - ptint list
 * @h: head
 * Return: size
 */
size_t plist(const list_me *h)
{
	size_t i = 0;

	while (h)
	{
		_puts_(cnvrt(h->n, 10, 0));
		_putchar_(':');
		_putchar_(' ');
		_puts_(h->s ? h->s : "(nil)");
		_puts_("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_ - node string
 * @h: head
 * @px: string
 * @c: char
 * Return: node or null
 */
list_me *node_starts_(list_me *h, char *px, char c)
{
	char *p = NULL;

	while (h)
	{
		p = _starts_(h->s, px);
		if (p && ((c == -1) || (*p == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * nodeget - index of node
 * @h: head
 * @node: node
 * Return: index or -1
 */
ssize_t nodeget(list_me *h, list_me *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
