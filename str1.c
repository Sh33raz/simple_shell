#include "shell.h"

/**
 * _dup_ - duplicates
 * @s: string
 * Return: pointer
 */
char *_dup_(const char *s)
{
	int len = 0;
	char *tmp;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	for (len++; len--;)
		tmp[len] = *--s;
	return (tmp);
}

/**
 *_puts_ - prints string
 *@s: string
 */
void _puts_(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar_(s[i]);
		i++;
	}
}

/**
 * _putchar_ - writes char
 * @c: char
 *
 * Return: 1 or -1
 */
int _putchar_(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 **_strncpy_ - copy string
 *@dest: dest
 *@src: src
 *@x: char
 *Return: string
 */
char *_strncpy_(char *dest, char *src, int x)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < x - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < x)
	{
		j = i;
		while (j < x)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat_ - concatenates strings
 *@dest: dest
 *@src: src
 *@x: char
 *Return: string
 */
char *_strncat_(char *dest, char *src, int x)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < x)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < x)
		dest[i] = '\0';
	return (s);
}
