#include "shell.h"

/**
 * buff_i - buffer
 * @h: struct
 * @buf: buffer
 * @len: address
 * Return: bytes
 */
ssize_t buff_i(me_t *h, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sigee);
#if USE_GETLINE
		y = getline(buf, &p, stdin);
#else
		y = _lineget(h, buf, &p);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0';
				y--;
			}
			h->line_flag = 1;
			rm_cmnts(*buf);
			histo_lst(h, *buf, h->histo_count++);
			{
				*len = y;
				h->buf_me = buf;
			}
		}
	}
	return (y);
}

/**
 * _nputget - gets a line
 * @h: struct
 * Return: bytes
 */
ssize_t _nputget(me_t *h)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t y = 0;
	char **pp = &(h->argu), *p;

	_putchar_(-1);
	y = buff_i(h, &buf, &len);
	if (y == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_checker(h, buf, &j, i, len);
		while (j < len)
		{
			if (chains_(h, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			h->buf_me_type = 0;
		}

		*pp = p;
		return (_len_(p));
	}

	*pp = buf;
	return (y);
}

/**
 * buff_r - reads buffer
 * @h: struct
 * @buf: buffer
 * @z: size
 * Return: y
 */
ssize_t buff_r(me_t *h, char *buf, size_t *z)
{
	ssize_t y = 0;

	if (*z)
		return (0);
	y = read(h->refd, buf, 1024);
	if (y >= 0)
		*z = y;
	return (y);
}

/**
 * _lineget - gets the next line
 * @h: struct
 * @ptr: pointer
 * @l: size
 * Return: z
 */
int _lineget(me_t *h, char **ptr, size_t *l)
{
	static char buf[1024];
	static size_t i, len;
	size_t j;
	ssize_t y = 0, z = 0;
	char *p = NULL, *pp = NULL, *c;

	p = *ptr;
	if (p && l)
		z = *l;
	if (i == len)
		i = len = 0;

	y = buff_r(h, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	c = _chara_(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	pp = _realloc_(p, z, z ? z + j : j + 1);
	if (!pp)
		return (p ? free(p), -1 : -1);

	if (z)
		_strncat_(pp, buf + i, j - i);
	else
		_strncpy_(pp, buf + i, j - i + 1);

	z += j - i;
	i = j;
	p = pp;

	if (l)
		*l = z;
	*ptr = p;
	return (z);
}

/**
 * _sigee - blocks ctrl-C
 * @num: number
 * Return: void
 */
void _sigee(__attribute__((unused))int num)
{
	_puts_("\n");
	_puts_("$ ");
	_putchar_(-1);
}
