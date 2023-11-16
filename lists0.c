#include "shell.h"

/**
 * nodes_ - adds node
 * @h: head
 * @s: string
 * @n: index
 * Return: size
 */
list_me *nodes_(list_me **h, const char *s, int n)
{
	list_me *_new;

	if (!h)
		return (NULL);
	_new = malloc(sizeof(list_me));
	if (!_new)
		return (NULL);
	_memoset((void *)_new, 0, sizeof(list_me));
	_new->n = n;
	if (s)
	{
		_new->s = _dup_(s);
		if (!_new->s)
		{
			free(_new);
			return (NULL);
		}
	}
	_new->next = *h;
	*h = _new;
	return (_new);
}

/**
 * nodeends_ - adds node to end
 * @h: head
 * @s: string
 * @n: index
 * Return: size
 */
list_me *nodeends_(list_me **h, const char *s, int n)
{
	list_me *_new, *node;

	if (!h)
		return (NULL);

	node = *h;
	_new = malloc(sizeof(list_me));
	if (!_new)
		return (NULL);
	_memoset((void *)_new, 0, sizeof(list_me));
	_new->n = n;
	if (s)
	{
		_new->s = _dup_(s);
		if (!_new->s)
		{
			free(_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = _new;
	}
	else
		*h = _new;
	return (_new);
}

/**
 * pliststr_ - prints string
 * @h: head
 * Return: size
 */
size_t pliststr_(const list_me *h)
{
	size_t i = 0;

	while (h)
	{
		_puts_(h->s ? h->s : "(nil)");
		_puts_("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rm_nodes_ - delete node
 * @h: head
 * @n: index
 * Return: 1 or 0
 */
int rm_nodes_(list_me **h, unsigned int n)
{
	list_me *node, *prev;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!n)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == n)
		{
			prev->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freelist - free nodes
 * @h: head
 */
void _freelist_(list_me **h)
{
	list_me *node, *next, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		next = node->next;
		free(node->s);
		free(node);
		node = next;
	}
	*h = NULL;
}
