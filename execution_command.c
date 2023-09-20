#include "main.h"

/**
 * is_cdir - checks ":" if is in the current directory.
 * @my_path: type char pointer char.
 * @m: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *my_path, int *m)
{
    if (my_path[*m] == ':')
        return (1);
    while (my_path[*m] != ':' && my_path[*m])
    {
        *m += 1;
    }
    if (my_path[*m])
        *m += 1;
    return (0);
}

/**
 * is_executable - determines if is an executable
 *
 * @ssh_list: lists structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(lists_shell *ssh_list)
{
    struct stat states;

    int m;

    char *my_input;

    my_input = ssh_list->args[0];
    for (m = 0; my_input[m]; m++)
    {
        if (my_input[m] == '.')
        {
            if (my_input[m + 1] == '.')
                return (0);
            if (my_input[m + 1] == '/')
                continue;
            else
                break;
        }
        else if (my_input[m] == '/' && m != 0)
        {
            if (my_input[m + 1] == '.')
                continue;
            m++;
            break;
        }
        else
            break;
    }
    if (m == 0)
        return (0);
    if (stat(my_input + m, &states) == 0)
    {
        return (m);
    }
    get_error(ssh_list, 127);
    return (-1);
}

/**
 * _which - locates a command
 *
 * @my_command: command name
 * @_environement: environment variable
 * Return: location of the command.
 */
char *_which(char *my_command, char **_environement)
{
    char *my_path, *my_ptr_pth, *my_tkn_pth, *dir;

    int my_l_directory, my_l_command, m;

    struct stat states;

    my_path = _getenv("PATH", _environement);
    if (my_path)
    {
        my_ptr_pth = _strdup(my_path);
        my_l_command = _strlen(my_command);
        my_tkn_pth = _strtok(my_ptr_pth, ":");
        m = 0;
        while (my_tkn_pth != NULL)
        {
            if (is_cdir(my_path, &m))
                if (stat(my_command, &states) == 0)
                    return (my_command);
            my_l_directory = _strlen(my_tkn_pth);
            dir = malloc(my_l_directory + my_l_command + 2);
            _strcpy(dir, my_tkn_pth);
            _strcat(dir, "/");
            _strcat(dir, my_command);
            _strcat(dir, "\0");
            if (stat(dir, &states) == 0)
            {
                free(my_ptr_pth);
                return (dir);
            }
            free(dir);
            my_tkn_pth = _strtok(NULL, ":");
        }
        free(my_ptr_pth);
        if (stat(my_command, &states) == 0)
            return (my_command);
        return (NULL);
    }
    if (my_command[0] == '/')
        if (stat(my_command, &states) == 0)
            return (my_command);
    return (NULL);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @my_directory: destination directory
 * @ssh_list: lists structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *my_directory, lists_shell *ssh_list)
{
    if (my_directory == NULL)
    {
        get_error(ssh_list, 127);
        return (1);
    }
    if (_strcmp(ssh_list->args[0], my_directory) != 0)
    {
        if (access(my_directory, X_OK) == -1)
        {
            get_error(ssh_list, 126);
            free(my_directory);
            return (1);
        }
        free(my_directory);
    }
    else
    {
        if (access(ssh_list->args[0], X_OK) == -1)
        {
            get_error(ssh_list, 126);
            return (1);
        }
    }
    return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @ssh_list: lists relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(lists_shell *ssh_list)
{

    int my_execution;

    pid_t my_wpd;

    pid_t my_pd;

    int my_state;

    char *my_directory;

    (void)my_wpd;

    my_execution = is_executable(ssh_list);
    if (my_execution == -1)
        return (1);
    if (my_execution == 0)
    {
        my_directory = _which(ssh_list->args[0], ssh_list->_environ);
        if (check_error_cmd(my_directory, ssh_list) == 1)
            return (1);
    }
    my_pd = fork();
    if (my_pd == 0)
    {
        if (my_execution == 0)
            my_directory = _which(ssh_list->args[0], ssh_list->_environ);
        else
            my_directory = ssh_list->args[0];
        execve(my_directory + my_execution, ssh_list->args, ssh_list->_environ);
    }
    else if (my_pd < 0)
    {
        perror(ssh_list->av[0]);
        return (1);
    }
    else
    {
        do
        {
            my_wpd = waitpid(my_pd, &my_state, WUNTRACED);
        } while (!WIFEXITED(my_state) && !WIFSIGNALED(my_state));
    }
    ssh_list->status = my_state / 256;
    return (1);
}
