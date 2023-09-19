#include "main.h"

/**
 * strcat_cd - this function will concatenate the message for cd error for us.
 * @listssh: lists ssh
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(lists_shell *listssh, char *msg, char *error, char *ver_str)
{
    char *ilgl_flg;

    _strcpy(error, listssh->av[0]);
    _strcat(error, ": ");
    _strcat(error, ver_str);
    _strcat(error, ": ");
    _strcat(error, listssh->args[0]);
    _strcat(error, msg);
    if (listssh->args[1][0] == '-')
    {
        ilgl_flg = malloc(3);
        ilgl_flg[0] = '-';
        ilgl_flg[1] = listssh->args[1][1];
        ilgl_flg[2] = '\0';
        _strcat(error, ilgl_flg);
        free(ilgl_flg);
    }
    else
        _strcat(error, listssh->args[1]);
    _strcat(error, "\n");
    _strcat(error, "\0");
    return (error);
}

/**
 * error_get_cd - this function will error message for cd command in get_cd for us.
 * @listssh: lists relevant (directory)
 * Return: Error message
 */
char *error_get_cd(lists_shell *listssh)
{
    char *err, *ver_str, *message;

    int l, l_id;

    ver_str = aux_itoa(listssh->counter);
    if (listssh->args[1][0] == '-')
    {
        message = ": Illegal option ";
        l_id = 2;
    }
    else
    {
        message = ": can't cd to ";
        l_id = _strlen(listssh->args[1]);
    }
    l = _strlen(listssh->av[0]) + _strlen(listssh->args[0]);
    l += _strlen(ver_str) + _strlen(message) + l_id + 5;
    err = malloc(sizeof(char) * (l + 1));
    if (err == 0)
    {
        free(ver_str);
        return (NULL);
    }
    err = strcat_cd(listssh, message, err, ver_str);
    free(ver_str);
    return (err);
}

/**
 * error_not_found - this function will generic error message for command not found for us.
 * @listssh: lists relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(lists_shell *listssh)
{
    int l;
    
    char *err;
    
    char *ver_str;

    ver_str = aux_itoa(listssh->counter);
    l = _strlen(listssh->av[0]) + _strlen(ver_str);
    l += _strlen(listssh->args[0]) + 16;
    err = malloc(sizeof(char) * (l + 1));
    if (err == 0)
    {
        free(err);
        free(ver_str);
        return (NULL);
    }
    _strcpy(err, listssh->av[0]);
    _strcat(err, ": ");
    _strcat(err, ver_str);
    _strcat(err, ": ");
    _strcat(err, listssh->args[0]);
    _strcat(err, ": not found\n");
    _strcat(err, "\0");
    free(ver_str);
    return (err);
}

/**
 * error_exit_shell - this function will generic error message for exit in get_exit for us.
 * @listssh: lists relevant (counter, arguments)
 * Return: Error message
 */
char *error_exit_shell(lists_shell *listssh)
{
    int l;
    
    char *err;
    
    char *ver_str;

    ver_str = aux_itoa(listssh->counter);
    l = _strlen(listssh->av[0]) + _strlen(ver_str);
    l += _strlen(listssh->args[0]) + _strlen(listssh->args[1]) + 23;
    err = malloc(sizeof(char) * (l + 1));
    if (err == 0)
    {
        free(ver_str);
        return (NULL);
    }
    _strcpy(err, listssh->av[0]);
    _strcat(err, ": ");
    _strcat(err, ver_str);
    _strcat(err, ": ");
    _strcat(err, listssh->args[0]);
    _strcat(err, ": Illegal number: ");
    _strcat(err, listssh->args[1]);
    _strcat(err, "\n\0");
    free(ver_str);
    return (err);
}
