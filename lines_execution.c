#include "main.h"

/**
 * exec_line - finds builtins and commands
 *
 * @ssh_list: lists relevant (args)
 * Return: 1 on success.
 */
int exec_line(lists_shell *ssh_list)
{
    int (*builtin)(lists_shell *listssh);

    if (ssh_list->args[0] == NULL)
        return (1);
    builtin = get_builtin(ssh_list->args[0]);
    if (builtin != NULL)
        return (builtin(ssh_list));
    return (cmd_exec(ssh_list));
}
