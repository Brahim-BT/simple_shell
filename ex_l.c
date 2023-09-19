#include "main.h"

/**
 * exec_line - this function will finds builtins and commands for us.
 * @listssh: lists relevant (args)
 * Return: 1 on success.
 */
int exec_line(lists_shell *listssh)
{
    int (*bltin)(lists_shell *listssh);

    if (listssh->args[0] == NULL)
        return (1);
    bltin = get_builtin(listssh->args[0]);
    if (bltin != NULL)
        return (bltin(listssh));
    return (cmd_exec(listssh));
}
