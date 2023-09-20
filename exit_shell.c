#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @ssh_list: lists relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(lists_shell *ssh_list)
{

    unsigned int my_status;

    int is_it_dgt;

    int my_str_l;

    int my_big_n;

    if (ssh_list->args[1] != NULL)
    {
        my_status = _atoi(ssh_list->args[1]);
        is_it_dgt = _isdigit(ssh_list->args[1]);
        my_str_l = _strlen(ssh_list->args[1]);
        my_big_n = my_status > (unsigned int)INT_MAX;
        if (!is_it_dgt || my_str_l > 10 || my_big_n)
        {
            get_error(ssh_list, 2);
            ssh_list->status = 2;
            return (1);
        }
        ssh_list->status = (my_status % 256);
    }
    return (0);
}
