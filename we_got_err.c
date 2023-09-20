#include "main.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @ssh_list: lists structure that contains arguments
 * @my_eval: error value
 * Return: error
 */
int get_error(lists_shell *ssh_list, int my_eval)
{
    char *my_err;

    switch (my_eval)
    {
    case -1:
        my_err = error_env(ssh_list);
        break;
    case 126:
        my_err = error_path_126(ssh_list);
        break;
    case 127:
        my_err = error_not_found(ssh_list);
        break;
    case 2:
        if (_strcmp("exit", ssh_list->args[0]) == 0)
            my_err = error_exit_shell(ssh_list);
        else if (_strcmp("cd", ssh_list->args[0]) == 0)
            my_err = error_get_cd(ssh_list);
        break;
    }
    if (my_err)
    {
        write(STDERR_FILENO, my_err, _strlen(my_err));
        free(my_err);
    }
    ssh_list->status = my_eval;
    return (my_eval);
}
