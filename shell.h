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
 *struct_info - info
 *@argu: args
 *@arguv: array of args
 *@pant: path
 *@arguc: arg count
 *@line_count: count
 *@er_num: err
 *@line_flag: flag
 *@funname: filename
 *@_envenv: copy env
 *@_envrn: env
 *@histo: history
 *@aliaz: alias
 *@env_cng: env changed
 *@stats: status
 *@buf_me: pointer
 *@buf_me_type: ||, &&, ;
 *@refd: fd
 *@histo_count: history count
 */
typedef struct info
{
	char *argu;
	char **arguv;
	char *pant;
	int arguc;
	unsigned int line_count;
	int er_num;
	int line_flag;
	char *funname;
	list_me *_envenv;
	list_me *histo;
	list_me *aliaz;
	char **_envrn;
	int env_cng;
	int stats;

	char **buf_me;
	int buf_me_type;
	int refd;
	int histo_count;
} me_t;

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

/* PATH.c */
int is_words(me_t *, char *);
char *duplc(char *, int, int);
char *path_finder(me_t *, char *, char *);

/* ERR_S.c */
void _errputs(char *);
int _errputchar(char);
int _putfind(char, int);
int _putsfind(char *, int);

/* STRINGS.c */
int _len_(char *);
int _cmp_(char *, char *);
char *_starts_(const char *, const char *);
char *_cat_(char *, char *);
char *_cpy_(char *, char *);
char *_dup_(const char *);
void _puts_(char *);
int _putchar_(char);
char *_strncpy_(char *, char *, int);
char *_strncat_(char *, char *, int);
char *_chara_(char *, char);
char **_strtow_(char *, char *);
char **_strtow2_(char *, char);

/* MEMORY.c */
char *_memoset(char *, char, unsigned int);
void _fr(char **);
void *_realloc_(void *, unsigned int, unsigned int);
int befree(void **);

/* TOOLS.c */
int me_int(me_t *);
int dilem(char, char *);
int _alpha_(int);
int _atotin(char *);
int _eratotin(char *);
void print_errs(me_t *, char *);
int dprint(int, int);
char *cnvrt(long int, int, int);
void rm_cmnts(char *);

/* BUILTIN.c */
int exit_me(me_t *);
int cd_me(me_t *);
int help_me(me_t *);
int hist_me(me_t *);
int a_unset(me_t *, char *);
int a_set(me_t *, char *);
int palias(list_me *);
int alias_me(me_t *);

/* GETLINE.c */
ssize_t buff_i(me_t *, char **, size_t *);
ssize_t _nputget(me_t *);
ssize_t buff_r(me_t *, char *, size_t *);
int _lineget(me_t *, char **, size_t *);
void _sigee(int);

/* MY.c module */
void clear_me(me_t *);
void set_me(me_t *, char **);
void free_me(me_t *, int);

/* ENV.c */
char *envget(me_t *, const char *);
int env_me(me_t *);
int setenv_me(me_t *);
int unsetenv_me(me_t *);
int _pplate(me_t *);
char **_environget(me_t *);
int _unsetenv(me_t *, char *);
int _setenv(me_t *, char *, char *);

/* IO.c */
char *historyget(me_t *h);
int wr_history(me_t *h);
int re_history(me_t *h);
int histo_lst(me_t *, char *, int);
int rename_histo(me_t *h);

/* LIST.c */
list_me *nodes_(list_me **, const char *, int);
list_me *nodeends_(list_me **, const char *, int);
size_t pliststr_(const list_me *);
int rm_nodes_(list_me **, unsigned int);
void _freelist_(list_me **);
size_t l_lists(const list_me *);
char **s_lists(list_me *);
size_t plist(const list_me *);
list_me *node_starts_(list_me *, char *, char);
ssize_t nodeget(list_me *, list_me *);

/* CHAIN.c */
int chains_(me_t *, char *, size_t *);
void chain_checker(me_t *, char *, size_t *, size_t, size_t);
int alias_rep(me_t *);
int vars_rep(me_t *);
int str_rep(char **, char *);

#endif
