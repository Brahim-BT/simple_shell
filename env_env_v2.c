#include "main.h"

/**
 * set_env - sets an environment variable
 *
 * @my_nm: name of the environment variable
 * @my_val: value of the environment variable
 * @ssh_list: lists structure (environ)
 * Return: no return
 */
void set_env(char *my_nm, char *my_val, lists_shell *ssh_list)
{
    int m;

    char *my_var_envirenment, *my_nm_env;

    for (m = 0; ssh_list->_environ[m]; m++)
    {
        my_var_envirenment = _strdup(ssh_list->_environ[m]);
        my_nm_env = _strtok(my_var_envirenment, "=");
        if (_strcmp(my_nm_env, my_nm) == 0)
        {
            free(ssh_list->_environ[m]);
            ssh_list->_environ[m] = copy_info(my_nm_env, my_val);
            free(my_var_envirenment);
            return;
        }
        free(my_var_envirenment);
    }
    ssh_list->_environ = _reallocdp(ssh_list->_environ, m, sizeof(char *) * (m + 2));
    ssh_list->_environ[m] = copy_info(my_nm, my_val);
    ssh_list->_environ[m + 1] = NULL;
}

/**
 * copy_info - copies info to create
 * a new env or alias
 * @my_nm: name (env or alias)
 * @my_val: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *my_nm, char *my_val)
{
    int my_l_nm, my_l_val, my_l;

    char *my_new_something;

    my_l_nm = _strlen(my_nm);
    my_l_val = _strlen(my_val);
    my_l = my_l_nm + my_l_val + 2;
    my_new_something = malloc(sizeof(char) * (my_l));
    _strcpy(my_new_something, my_nm);
    _strcat(my_new_something, "=");
    _strcat(my_new_something, my_val);
    _strcat(my_new_something, "\0");
    return (my_new_something);
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @ssh_list: lists relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(lists_shell *ssh_list)
{
    if (ssh_list->args[1] == NULL || ssh_list->args[2] == NULL)
    {
        get_error(ssh_list, -1);
        return (1);
    }
    set_env(ssh_list->args[1], ssh_list->args[2], ssh_list);
    return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @ssh_list: lists relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(lists_shell *ssh_list)
{

    char **my_rlc_environ;

    char *my_var_env, *my_nm_env;

    int m, n, o;

    if (ssh_list->args[1] == NULL)
    {
        get_error(ssh_list, -1);
        return (1);
    }
    o = -1;
    for (m = 0; ssh_list->_environ[m]; m++)
    {
        my_var_env = _strdup(ssh_list->_environ[m]);
        my_nm_env = _strtok(my_var_env, "=");
        if (_strcmp(my_nm_env, ssh_list->args[1]) == 0)
        {
            o = m;
        }
        free(my_var_env);
    }
    if (o == -1)
    {
        get_error(ssh_list, -1);
        return (1);
    }
    my_rlc_environ = malloc(sizeof(char *) * (m));
    for (m = n = 0; ssh_list->_environ[m]; m++)
    {
        if (m != o)
        {
            my_rlc_environ[n] = ssh_list->_environ[m];
            n++;
        }
    }
    my_rlc_environ[n] = NULL;
    free(ssh_list->_environ[o]);
    free(ssh_list->_environ);
    ssh_list->_environ = my_rlc_environ;
    return (1);
}
