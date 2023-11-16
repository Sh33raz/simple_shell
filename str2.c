#include "shell.h"

/**
 * _chara_ - locate char
 * @s: string
 * @c: char
 * Return: NULL
 */
char *_chara_(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * _strtow_ - splits
 * @s: string
 * @d: delimeter
 * Return: pointer
 */
char **_strtow_(char *s, char *d)
{
	int i, j, k, x, num = 0;
	char **z;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!dilem(s[i], d) && (dilem(s[i + 1], d) || !s[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	z = malloc((1 + num) * sizeof(char *));
	if (!z)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (dilem(s[i], d))
			i++;
		k = 0;
		while (!dilem(s[i + k], d) && s[i + k])
			k++;
		z[j] = malloc((k + 1) * sizeof(char));
		if (!z[j])
		{
			for (k = 0; k < j; k++)
				free(z[k]);
			free(z);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			z[j][x] = s[i++];
		z[j][x] = 0;
	}
	z[j] = NULL;
	return (z);
}

/**
 * _strtow2_ - splits
 * @s: string
 * @d: delimeter
 * Return: pointer
 */
char **_strtow2_(char *s, char d)
{
	int i, j, k, x, num = 0;
	char **z;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != d && s[i + 1] == d) || (s[i] != d && !s[i + 1]) || s[i + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	z = malloc((1 + num) * sizeof(char *));
	if (!z)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (s[i] == d && s[i] != d)
			i++;
		k = 0;
		while (s[i + k] != d && s[i + k] && s[i + k] != d)
			k++;
		z[j] = malloc((k + 1) * sizeof(char));
		if (!z[j])
		{
			for (k = 0; k < j; k++)
				free(z[k]);
			free(z);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			z[j][x] = s[i++];
		z[j][x] = 0;
	}
	z[j] = NULL;
	return (z);
}
