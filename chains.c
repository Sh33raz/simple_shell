#include "shell.h"

/**
 * chains_ - chain delimeter
 * @h: struct
 * @buf: buffer
 * @p: pointer
 * Return: 1 or 0
 */
int chains_(me_t *h, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		h->buf_me_type = 1;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		h->buf_me_type = 2;
	}
	else if (buf[x] == ';')
	{
		buf[x] = 0;
		h->buf_me_type = 3;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * chain_checker - checks chain
 * @h: struct
 * @buf: buffer
 * @p: pointer
 * @i: start
 * @len: length
 */
void chain_checker(me_t *h, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (h->buf_me_type == 2)
	{
		if (h->stats)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (h->buf_me_type == 1 )
	{
		if (!h->stats)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * alias_rep - replace alias
 * @h: struct
 * Return: 1 or 0
 */
int alias_rep(me_t *h)
{
	int i;
	list_me *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_(h->aliaz, h->arguv[0], '=');
		if (!node)
			return (0);
		free(h->arguv[0]);
		p = _chara_(node->s, '=');
		if (!p)
			return (0);
		p = _dup_(p + 1);
		if (!p)
			return (0);
		h->arguv[0] = p;
	}
	return (1);
}

/**
 * vars_rep - replace vars
 * @h: struct
 * Return: 1 or 0
 */
int vars_rep(me_t *h)
{
	int i = 0;
	list_me *node;

	for (i = 0; h->arguv[i]; i++)
	{
		if (h->arguv[i][0] != '$' || !h->arguv[i][1])
			continue;

		if (!_cmp_(h->arguv[i], "$?"))
		{
			str_rep(&(h->arguv[i]),
				_dup_(cnvrt(h->stats, 10, 0)));
			continue;
		}
		if (!_cmp_(h->arguv[i], "$$"))
		{
			str_rep(&(h->arguv[i]),
				_dup_(cnvrt(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_(h->_envenv, &h->arguv[i][1], '=');
		if (node)
		{
			str_rep(&(h->arguv[i]),
				_dup_(_chara_(node->s, '=') + 1));
			continue;
		}
		str_rep(&h->arguv[i], _dup_(""));

	}
	return (0);
}

/**
 * str_rep - replaces string
 * @o: old string
 * @n: new string
 * Return: 1 or 0
 */
int str_rep(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
