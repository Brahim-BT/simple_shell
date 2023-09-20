#include "main.h"

/**
 * error_get_cd - error message for cd command in get_cd
 * @ssh_list: lists relevant (directory)
 * Return: Error message
 */
char *error_get_cd(lists_shell *ssh_list)
{
    char *my_err, *my_ver_string, *my_message;

    int my_l, my_l_id;

    my_ver_string = aux_itoa(ssh_list->counter);
    if (ssh_list->args[1][0] == '-')
    {
        my_message = ": Illegal option ";
        my_l_id = 2;
    }
    else
    {
        my_message = ": can't cd to ";
        my_l_id = _strlen(ssh_list->args[1]);
    }
    my_l = _strlen(ssh_list->av[0]) + _strlen(ssh_list->args[0]);
    my_l += _strlen(my_ver_string) + _strlen(my_message) + my_l_id + 5;
    my_err = malloc(sizeof(char) * (my_l + 1));
    if (my_err == 0)
    {
        free(my_ver_string);
        return (NULL);
    }
    my_err = strcat_cd(ssh_list, my_message, my_err, my_ver_string);
    free(my_ver_string);
    return (my_err);
}

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @ssh_list: lists relevant (directory)
 * @my_message: message to print
 * @my_err: output message
 * @my_ver_string: counter lines
 * Return: error message
 */
char *strcat_cd(lists_shell *ssh_list, char *my_message, char *my_err, char *my_ver_string)
{
    char *some_ilgl_flag;

    _strcpy(my_err, ssh_list->av[0]);
    _strcat(my_err, ": ");
    _strcat(my_err, my_ver_string);
    _strcat(my_err, ": ");
    _strcat(my_err, ssh_list->args[0]);
    _strcat(my_err, my_message);
    if (ssh_list->args[1][0] == '-')
    {
        some_ilgl_flag = malloc(3);
        some_ilgl_flag[0] = '-';
        some_ilgl_flag[1] = ssh_list->args[1][1];
        some_ilgl_flag[2] = '\0';
        _strcat(my_err, some_ilgl_flag);
        free(some_ilgl_flag);
    }
    else
    {
        _strcat(my_err, ssh_list->args[1]);
    }
    _strcat(my_err, "\n");
    _strcat(my_err, "\0");
    return (my_err);
}

/**
 * error_not_found - generic error message for command not found
 * @ssh_list: lists relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(lists_shell *ssh_list)
{

    int my_l;

    char *my_err;

    char *my_ver_string;

    my_ver_string = aux_itoa(ssh_list->counter);
    my_l = _strlen(ssh_list->av[0]) + _strlen(my_ver_string);
    my_l += _strlen(ssh_list->args[0]) + 16;
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
    _strcat(my_err, ": not found\n");
    _strcat(my_err, "\0");
    free(my_ver_string);
    return (my_err);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @ssh_list: lists relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(lists_shell *ssh_list)
{

    int my_l;

    char *my_err;

    char *my_ver_string;

    my_ver_string = aux_itoa(ssh_list->counter);
    my_l = _strlen(ssh_list->av[0]) + _strlen(my_ver_string);
    my_l += _strlen(ssh_list->args[0]) + _strlen(ssh_list->args[1]) + 23;
    my_err = malloc(sizeof(char) * (my_l + 1));
    if (my_err == 0)
    {
        free(my_ver_string);
        return (NULL);
    }
    _strcpy(my_err, ssh_list->av[0]);
    _strcat(my_err, ": ");
    _strcat(my_err, my_ver_string);
    _strcat(my_err, ": ");
    _strcat(my_err, ssh_list->args[0]);
    _strcat(my_err, ": Illegal number: ");
    _strcat(my_err, ssh_list->args[1]);
    _strcat(my_err, "\n\0");
    free(my_ver_string);
    return (my_err);
}
