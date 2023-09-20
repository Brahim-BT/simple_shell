#include "main.h"

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(lists_shell *)
{
    builtin_t blt_in[] = {
        {"env", _env},
        {"exit", exit_shell},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"cd", cd_shell},
        {"help", get_help},
        {NULL, NULL}};

    int m;

    m = 0;
    while (blt_in[m].name)
    {
        if (_strcmp(blt_in[m].name, cmd) == 0)
            break;
        m++;
    }
    return (blt_in[m].f);
}
