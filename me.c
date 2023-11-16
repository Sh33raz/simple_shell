#include "shell.h"

/**
 * clear_me - my_t struct
 * @h: struct
 */
void clear_me(me_t *h)
{
	h->argu = NULL;
	h->arguv = NULL;
	h->pant = NULL;
	h->arguc = 0;
}

/**
 * set_me - me_t struct
 * @h: struct
 * @av: argument
 */
void set_me(me_t *h, char **av)
{
	int i = 0;

	h->funname = av[0];
	if (h->argu)
	{
		h->arguv = _strtow_(h->argu, " \t");
		if (!h->arguv)
		{

			h->arguv = malloc(sizeof(char *) * 2);
			if (h->arguv)
			{
				h->arguv[0] = _dup_(h->argu);
				h->arguv[1] = NULL;
			}
		}
		for (i = 0; h->arguv && h->arguv[i]; i++)
			;
		h->arguc = i;

		alias_rep(h);
		vars_rep(h);
	}
}

/**
 * free_me - frees me_t struct
 * @h: struct
 * @a: true if free
 */
void free_me(me_t *h, int a)
{
	_fr(h->arguv);
	h->arguv = NULL;
	h->pant = NULL;
	if (a)
	{
		if (!h->buf_me)
			free(h->argu);
		if (h->_envenv)
			_freelist_(&(h->_envenv));
		if (h->histo)
			_freelist_(&(h->histo));
		if (h->aliaz)
			_freelist_(&(h->aliaz));
		_fr(h->_envrn);
			h->_envrn = NULL;
		befree((void **)h->buf_me);
		if (h->refd > 2)
			close(h->refd);
		_putchar_(-1);
	}
}
