#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @ssh_list: lists relevant
 * Return: 1 on success
 */
int cd_shell(lists_shell *ssh_list)
{
    char *directory;

    int is_dsh, is_hm2, is_hm;

    directory = ssh_list->args[1];
    if (directory != NULL)
    {
        is_hm = _strcmp("$HOME", directory);
        is_hm2 = _strcmp("~", directory);
        is_dsh = _strcmp("--", directory);
    }
    if (directory == NULL || !is_hm || !is_hm2 || !is_dsh)
    {
        cd_to_home(ssh_list);
        return (1);
    }
    if (_strcmp("-", directory) == 0)
    {
        cd_previous(ssh_list);
        return (1);
    }
    if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
    {
        cd_dot(ssh_list);
        return (1);
    }
    cd_to(ssh_list);
    return (1);
}
