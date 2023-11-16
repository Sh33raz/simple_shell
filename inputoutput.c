#include "shell.h"

/**
 * historyget - gets history
 * @h: struct
 * Return: string
 */

char *historyget(me_t *h)
{
	char *buf, *d;

	d = envget(h, "HOME=");
	if (!d)
		return (NULL);
	buf = malloc(sizeof(char) * (_len_(d) + _len_(".simple_shell_history") + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_cpy_(buf, d);
	_cat_(buf, "/");
	_cat_(buf, ".simple_shell_histor");
	return (buf);
}

/**
 * wr_history - create file
 * @h: struct
 * Return: 1 or -1
 */
int wr_history(me_t *h)
{
	ssize_t fd;
	char *fn = historyget(h);
	list_me *node = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (node = h->histo; node; node = node->next)
	{
		_putsfind(node->s, fd);
		_putfind('\n', fd);
	}
	_putfind(-1, fd);
	close(fd);
	return (1);
}

/**
 * re_history - reads history
 * @h: struct
 * Return: 0 or else
 */
int re_history(me_t *h)
{
	int i, last = 0, l = 0;
	ssize_t fd, len, fs = 0;
	struct stat st;
	char *buf = NULL, *fn = historyget(h);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	buf = malloc(sizeof(char) * (fs + 1));
	if (!buf)
		return (0);
	len = read(fd, buf, fs);
	buf[fs] = 0;
	if (len <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fs; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			histo_lst(h, buf + last, l++);
			last = i + 1;
		}
	if (last != i)
		histo_lst(h, buf + last, l++);
	free(buf);
	h->histo_count = l;
	while (h->histo_count-- >= 4096)
		rm_nodes_(&(h->histo), 0);
	rename_histo(h);
	return (h->histo_count);
}

/**
 * histo_lst - adds to history
 * @h: Struct
 * @buf: buffer
 * @l: linecount
 * Return: Always 0
 */
int histo_lst(me_t *h, char *buf, int l)
{
	list_me *node = NULL;

	if (h->histo)
		node = h->histo;
	nodeends_(&node, buf, l);

	if (!h->histo)
		h->histo = node;
	return (0);
}

/**
 * rename_histo - renumbers history
 * @h: Struct
 * Return: count
 */
int rename_histo(me_t *h)
{
	list_me *node = h->histo;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (h->histo_count = i);
}
