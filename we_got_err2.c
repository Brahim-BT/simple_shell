#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @ssh_list: lists relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(lists_shell *ssh_list)
{

    int my_l;

    char *my_err;

    char *my_ver_string;

    char *my_message;

    my_ver_string = aux_itoa(ssh_list->counter);
    my_message = ": Unable to add/remove from environment\n";
    my_l = _strlen(ssh_list->av[0]) + _strlen(my_ver_string);
    my_l += _strlen(ssh_list->args[0]) + _strlen(my_message) + 4;
    my_err = malloc(sizeof(char) * (my_l + 1));
    if (my_err == 0)
    {
        free(my_err);
        free(my_ver_string);
        return (NULL);
    }
    _strcpy(my_err, ssh_list->av[0]);
    _strcat(my_err, ": ");
    _strcat(my_err, my_ver_string);
    _strcat(my_err, ": ");
    _strcat(my_err, ssh_list->args[0]);
    _strcat(my_err, my_message);
    _strcat(my_err, "\0");
    free(my_ver_string);
    return (my_err);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @ssh_list: lists relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(lists_shell *ssh_list)
{

    int my_l;

    char *my_err;

    char *my_ver_string;

    my_ver_string = aux_itoa(ssh_list->counter);
    my_l = _strlen(ssh_list->av[0]) + _strlen(my_ver_string);
    my_l += _strlen(ssh_list->args[0]) + 24;
    my_err = malloc(sizeof(char) * (my_l + 1));
    if (my_err == 0)
    {
        free(my_err);
        free(my_ver_string);
        return (NULL);
    }
    _strcpy(my_err, ssh_list->av[0]);
    _strcat(my_err, ": ");
    _strcat(my_err, my_ver_string);
    _strcat(my_err, ": ");
    _strcat(my_err, ssh_list->args[0]);
    _strcat(my_err, ": Permission denied\n");
    _strcat(my_err, "\0");
    free(my_ver_string);
    return (my_err);
}
