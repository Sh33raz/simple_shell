#include "shell.h"

/**
 * print_errs - error message
 * @h: struct
 * @s: string
 * Return: 0 or -1
 */
void print_errs(me_t *h, char *s)
{
	_errputs(h->funname);
	_errputs(": ");
	dprint(h->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(h->arguv[0]);
	_errputs(": ");
	_errputs(s);
}

/**
 * dprint - prints base 10
 * @x: input
 * @fd: filedescriptor
 * Return: int
 */
int dprint(int x, int fd)
{
	int (*words)(char) = _putchar_;
	int i, num = 0;
	unsigned int mtlq, tmp;

	if (fd == STDERR_FILENO)
		words = _errputchar;
	if (x < 0)
	{
		mtlq = -x;
		words('-');
		num++;
	}
	else
		mtlq = x;
	tmp = mtlq;
	for (i = 100000000; i > 1; i /= 10)
	{
		if (mtlq / i)
		{
			words('0' + tmp / i);
			num++;
		}
		tmp %= i;
	}
	words('0' + tmp);
	num++;

	return (num);
}

/**
 * cnvrt - clone of itoa
 * @num: number
 * @b: base
 * @f: flags
 * Return: string
 */
char *cnvrt(long int num, int b, int f)
{
	static char *a;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(f & 2) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	a = f & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do	{
		*--p = a[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * rm_cmnts - replaces '#' with '\0'
 * @p: pointer
 * Return: Always 0;
 */
void rm_cmnts(char *p)
{
	int i;

	for (i = 0; p[i] != '\0'; i++)
		if (p[i] == '#' && (!i || p[i - 1] == ' '))
		{
			p[i] = '\0';
			break;
		}
}
