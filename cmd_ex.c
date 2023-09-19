#include "main.h"

/**
 * is_cdir - this function will check ":" if is in the current directory for us.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 or 0.
 */
int is_cdir(char *path, int *i)
{
    if (path[*i] == ':')
        return (1);
    while (path[*i] != ':' && path[*i])
        *i += 1;
    if (path[*i])
        *i += 1;
    return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
    char *pth, *ptr_pth, *tkn_pth, *directory;

    struct stat st;

    int l_dir, l_cmd, n;

    pth = _getenv("PATH", _environ);
    if (pth)
    {
        ptr_pth = _strdup(pth);
        l_cmd = _strlen(cmd);
        tkn_pth = _strtok(ptr_pth, ":");
        n = 0;
        while (tkn_pth != NULL)
        {
            if (is_cdir(pth, &n))
                if (stat(cmd, &st) == 0)
                    return (cmd);
            l_dir = _strlen(tkn_pth);
            directory = malloc(l_dir + l_cmd + 2);
            _strcpy(directory, tkn_pth);
            _strcat(directory, "/");
            _strcat(directory, cmd);
            _strcat(directory, "\0");
            if (stat(directory, &st) == 0)
            {
                free(ptr_pth);
                return (directory);
            }
            free(directory);
            tkn_pth = _strtok(NULL, ":");
        }
        free(ptr_pth);
        if (stat(cmd, &st) == 0)
            return (cmd);
        return (NULL);
    }
    if (cmd[0] == '/')
        if (stat(cmd, &st) == 0)
            return (cmd);
    return (NULL);
}

/**
 * is_extble - this function will determine if is an executable for us.
 * @listssh: lists structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_extble(lists_shell *listssh)
{
    struct stat st;

    char *input;

    int n;

    input = listssh->args[0];
    n = 0;
    while (input[n])
    {
        if (input[n] == '.')
        {
            if (input[n + 1] == '.')
                return (0);
            if (input[n + 1] == '/')
                continue;
            else
                break;
        }
        else if (input[n] == '/' && n != 0)
        {
            if (input[n + 1] == '.')
                continue;
            n++;
            break;
        }
        else
            break;
        n++;
    }
    if (n == 0)
        return (0);

    if (stat(input + n, &st) == 0)
    {
        return (n);
    }
    get_error(listssh, 127);
    return (-1);
}

/**
 * err_cmd - this function will verifies if user has permissions to access for us.
 * @dir: destination directory
 * @listssh: lists structure
 * Return: 1 or 0.
 */
int err_cmd(char *dir, lists_shell *listssh)
{
    if (dir == NULL)
    {
        get_error(listssh, 127);
        return (1);
    }
    if (_strcmp(listssh->args[0], dir) != 0)
    {
        if (access(dir, X_OK) == -1)
        {
            get_error(listssh, 126);
            free(dir);
            return (1);
        }
        free(dir);
    }
    else
    {
        if (access(listssh->args[0], X_OK) == -1)
        {
            get_error(listssh, 126);
            return (1);
        }
    }
    return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @listssh: lists relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(lists_shell *listssh)
{
    pid_t pd;
    
    int st;
    
    pid_t wpd;
    
    (void)wpd;
    
    char *directory;
    
    int ex;

    ex = is_extble(listssh);
    if (ex == -1)
        return (1);
    if (ex == 0)
    {
        directory = _which(listssh->args[0], listssh->_environ);
        if (err_cmd(directory, listssh) == 1)
            return (1);
    }
    pd = fork();
    if (pd == 0)
    {
        if (ex == 0)
            directory = _which(listssh->args[0], listssh->_environ);
        else
            directory = listssh->args[0];
        execve(directory + ex, listssh->args, listssh->_environ);
    }
    else if (pd < 0)
    {
        perror(listssh->av[0]);
        return (1);
    }
    else
    {
        do
        {
            wpd = waitpid(pd, &st, WUNTRACED);
        } while (!WIFEXITED(st) && !WIFSIGNALED(st));
    }
    listssh->status = st / 256;
    return (1);
}
