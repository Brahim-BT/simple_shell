#include "main.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @ssh_list: lists structure (args and input)
 * Return: Return 0
 */
int get_help(lists_shell *ssh_list)
{
    if (ssh_list->args[1] == 0)
        aux_help_general();
    else if (_strcmp(ssh_list->args[1], "setenv") == 0)
        aux_help_setenv();
    else if (_strcmp(ssh_list->args[1], "env") == 0)
        aux_help_env();
    else if (_strcmp(ssh_list->args[1], "unsetenv") == 0)
        aux_help_unsetenv();
    else if (_strcmp(ssh_list->args[1], "help") == 0)
        aux_help();
    else if (_strcmp(ssh_list->args[1], "exit") == 0)
        aux_help_exit();
    else if (_strcmp(ssh_list->args[1], "cd") == 0)
        aux_help_cd();
    else if (_strcmp(ssh_list->args[1], "alias") == 0)
        aux_help_alias();
    else
        write(STDERR_FILENO, ssh_list->args[0],
              _strlen(ssh_list->args[0]));

    ssh_list->status = 0;
    return (1);
}
