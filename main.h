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

#define BUFFERSIZE 1024
#define TOK_BUFFERSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

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

int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_extble(lists_shell *listssh);
int err_cmd(char *dir, lists_shell *listssh);
int cmd_exec(lists_shell *listssh);

int cmp_env_name(const char *nenv, const char *name);
char *_getenv(const char *name, char **_environ);
int _env(lists_shell *listssh);

char *copy_info(char *name, char *value);
void set_env(char *name, char *value, lists_shell *listssh);
int _setenv(lists_shell *listssh);
int _unsetenv(lists_shell *listssh);

int get_error(lists_shell *listssh, int eval);

char *strcat_cd(lists_shell *listssh, char *msg, char *error, char *ver_str);
char *error_get_cd(lists_shell *listssh);
char *error_not_found(lists_shell *listssh);
char *error_exit_shell(lists_shell *listssh);

char *error_env(lists_shell *listssh);
char *error_path_126(lists_shell *listssh);

int exec_line(lists_shell *listssh);

int exit_shell(lists_shell *listssh);

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void get_sigint(int sig);

void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

#endif