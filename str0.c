#include "shell.h"

/**
 * _len_ - length string
 * @s: string
 * Return: length of string
 */
int _len_(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _cmp_ - comparison of two strangs.
 * @s1: string
 * @s2: string
 * Return: + or - or 0
 */
int _cmp_(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _starts_ - starts
 * @hay: string
 * @n: substring
 * Return: pointer
 */
char *_starts_(const char *hay, const char *n)
{
	while (*n)
		if (*n++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _cat_ - concatenates
 * @dest: dest
 * @src: src
 * Return: dest
 */
char *_cat_(char *dest, char *src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (tmp);
}

/**
 * _cpy_ - copy
 * @dest: dest
 * @src: src
 * Return: dest
 */
char *_cpy_(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
