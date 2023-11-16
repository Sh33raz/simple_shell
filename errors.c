#include "shell.h"

/**
 *_errputs - prints string
 * @s: string
 */
void _errputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_errputchar(s[i]);
		i++;
	}
}

/**
 * _errputchar - character to stderr
 * @c: char
 * Return: 1 or -1
 */
int _errputchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _putfind - character to fd
 * @c: char
 * @fd: filedescriptor
 * Return: 1 or -1
 */
int _putfind(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfind - prints string
 * @s: string
 * @fd: filedescriptor
 * Return: i
 */
int _putsfind(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putfind(*s++, fd);
	}
	return (i);
}
