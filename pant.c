#include "shell.h"

/**
 * is_words - command
 * @h: struct
 * @pa: path
 * Return: 1 or 0
 */
int is_words(me_t *h, char *pa)
{
	struct stat st;

	(void)h;
	if (!pa || stat(pa, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplc - duplicates
 * @pa: PATH
 * @strt: start
 * @stp: stop
 *
 * Return: pointer to new buffer
 */
char *duplc(char *pa, int strt, int stp)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = strt; i < stp; i++)
		if (pa[i] != ':')
			buf[j++] = pa[i];
	buf[j] = 0;
	return (buf);
}

/**
 * path_finder - find PATH
 * @h: struct
 * @pa: PATH
 * @klam: cmd
 *
 * Return: path or NULL
 */
char *path_finder(me_t *h, char *pa, char *words)
{
	int i = 0, pos = 0;
	char *path;

	if (!pa)
		return (NULL);
	if ((_len_(words) > 2) && _starts_(words, "./"))
	{
		if (is_words(h, words))
			return (words);
	}
	while (1)
	{
		if (!pa[i] || pa[i] == ':')
		{
			path = duplc(pa, pos, i);
			if (!*path)
				_cat_(path, words);
			else
			{
				_cat_(path, "/");
				_cat_(path, words);
			}
			if (is_words(h, path))
				return (path);
			if (!pa[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}
