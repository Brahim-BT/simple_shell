#ifndef _MAIN_
#define _MAIN_
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include <sys/stat.h>

/**
 * struct lists - struct lists
 * @av: String pointer
 * @input: String
 * @args: String
 * @status: Integer
 * @counter: Integer
 * @_environ: String
 * @pid: String
 */
typedef struct lists
{
    char **args;
    char *input;
    char **av;
    int status;
    int counter;
    char *pid;
    char **_environ;
} lists_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: char
 * @next: next node
 * Description: single linked list
 */
typedef struct sep_list_s
{
    char separator;
    struct sep_list_s *next;
} sep_list;

/**
 * struct list_s - single linked list
 * @line: Char
 * @next: next node
 * Description: single linked list
 */
typedef struct list_s
{
    char *line;
    struct list_s *next;
} line_list;

/**
 * struct var_list - single linked list
 * @len_var: Integer
 * @val: String
 * @len_val: Integer
 * @next: next node
 * Description: single linked list
 */
typedef struct var_list
{
    int len_var;
    char *val;
    int len_val;
    struct var_list *next;
} r_var;

/**
 * struct builtins_s - Builtin struct
 * @name: String
 * @f: function pointer
 */
typedef struct builtins_s
{
    char *name;
    int (*f)(lists_shell *listssh);
} builtin_t;

int (*get_combltin(char *cmd))(lists_shell *listssh);

int cd_command(lists_shell *listssh);
void cd_d(lists_shell *listssh);
void cd_t(lists_shell *listssh);
void cd_pre(lists_shell *listssh);
void cd_hm(lists_shell *listssh);

int rptd_chr(char *input, int i);
int err_sp_op(char *input, int i, char last);
int frst_chr(char *input, int *i);
void print_syntx_err(lists_shell *listssh, char *input, int i, int bool);
int syntx_err(lists_shell *listssh, char *input);


#endif