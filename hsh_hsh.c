#include "shell.h"

/**
 * hsh - main shell loop
 * @f: the parameter & return f struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *f, char **av)
{
    int bltn_retro = 0;

    ssize_t x = 0;

    while (x != -1 && bltn_retro != -2)
    {
        clear_info(f);
        if (interactive(f))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        x = get_input(f);
        if (x != -1)
        {
            set_info(f, av);
            bltn_retro = find_builtin(f);
            if (bltn_retro == -1)
                find_cmd(f);
        }
        else if (interactive(f))
            _putchar('\n');
        free_info(f, 0);
    }
    write_history(f);
    free_info(f, 1);
    if (!interactive(f) && f->status)
        exit(f->status);
    if (bltn_retro == -2)
    {
        if (f->err_num == -1)
            exit(f->status);
        exit(f->err_num);
    }
    return (bltn_retro);
}

/**
 * find_builtin - finds a builtin command
 * @f: the parameter & return f struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *f)
{
    int m, built_in_ret = -1;

    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}};

    for (m = 0; builtintbl[m].type; m++)
        if (_strcmp(f->argv[0], builtintbl[m].type) == 0)
        {
            f->line_count++;
            built_in_ret = builtintbl[m].func(f);
            break;
        }
    return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @f: the parameter & return f struct
 *
 * Return: void
 */
void find_cmd(info_t *f)
{
    int m, o;

    char *path = NULL;

    f->path = f->argv[0];
    if (f->linecount_flag == 1)
    {
        f->line_count++;
        f->linecount_flag = 0;
    }
    for (m = 0, o = 0; f->arg[m]; m++)
        if (!is_delim(f->arg[m], " \t\n"))
            o++;
    if (!o)
        return;
    path = find_path(f, _getenv(f, "PATH="), f->argv[0]);
    if (path)
    {
        f->path = path;
        fork_cmd(f);
    }
    else
    {
        if ((interactive(f) || _getenv(f, "PATH=") || f->argv[0][0] == '/') && is_cmd(f, f->argv[0]))
            fork_cmd(f);
        else if (*(f->arg) != '\n')
        {
            f->status = 127;
            print_error(f, "not found\n");
        }
    }
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @f: the parameter & return f struct
 *
 * Return: void
 */
void fork_cmd(info_t *f)
{
    pid_t chld_pid;

    chld_pid = fork();
    if (chld_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (chld_pid == 0)
    {
        if (execve(f->path, f->argv, get_environ(f)) == -1)
        {
            free_info(f, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(f->status));
        if (WIFEXITED(f->status))
        {
            f->status = WEXITSTATUS(f->status);
            if (f->status == 126)
                print_error(f, "Permission denied\n");
        }
    }
}
