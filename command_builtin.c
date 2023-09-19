#include "main.h"

/**
 * get_builtin - get the builtin function for us in the command in the arg
 * @cmd: command argument
 * Return: the pointer function of the builtin command
 */

int (*get_combltin(char *cmd))(lists_shell *)
{
    builtin_t blt_arg[] = {
        {"exit", exit_shell},
        {"setenv", _setenv},
        {"help", get_help},
        {"env", _env},
        {"cd", cd_shell},
        {"unsetenv", _unsetenv},
        {NULL, NULL}};
    int n;

    for (n = 0; blt_arg[n].name; n++)
    {
        if (_strcmp(blt_arg[n].name, cmd) == 0)
            break;
    }
    return (blt_arg[n].f);
}
