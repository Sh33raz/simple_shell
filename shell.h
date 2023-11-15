#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;


/**
 * str_list - singly linked list
 * @n: the number field
 * @s: string
 * @next: next
 */
typedef struct str_list
{
	int n;
	char *s;
	struct str_list *next;
} list_me;

/**
 *strust_info - info
 *@arg: args
 *@argv: array of args
 *@pa: path
 *@argc: arg count
 *@l_count: count
 *@err_num: err
 *@l_flag: flag
 *@fname: filename
 *@_env: copy env
 *@_environ: env
 *@history: history
 *@alias: alias
 *@env_ch: env changed
 *@status: status
 *@klam_buf: pointer
 *@klam_buf_type: ||, &&, ;
 *@readfd: fd
 *@h_count: history count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *pa;
	int argc;
	unsigned int l_count;
	int err_num;
	int l_flag;
	char *fname;
	list_me *_env;
	list_me *history;
	list_me *alias;
	char **_environ;
	int env_ch;
	int status;

	char **buf_me;
	int buf_me_type;
	int readfd;
	int h_count;
} me _t;

#define _INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin
 *@t: flag
 *@f: function
 */
typedef struct builtin
{
	char *t;
	int (*f)(me_t *);
} built_me;


/* HSH.c */
int hsh(me_t *, char **);
int find_blt(me_t *);
void find_words(me_t *);
void fork_words(me_t *);

#endif
