#include "main.h"

/**
 * copy_info - this function will copy info to create a new env or alias for us.
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
    int l_nm, l_val, l;

    char *new;

    l_nm = _strlen(name);
    l_val = _strlen(value);
    l = l_nm + l_val + 2;
    new = malloc(sizeof(char) * (l));
    _strcpy(new, name);
    _strcat(new, "=");
    _strcat(new, value);
    _strcat(new, "\0");
    return (new);
}

/**
 * set_env - this function will set an environment variable for us.
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @listssh: lists structure (environ)
 * Return: void
 */
void set_env(char *name, char *value, lists_shell *listssh)
{
    char *v_env, *nm_env;

    int n;

    n = 0;
    while (listssh->_environ[n])
    {
        v_env = _strdup(listssh->_environ[n]);
        nm_env = _strtok(v_env, "=");
        if (_strcmp(nm_env, name) == 0)
        {
            free(listssh->_environ[n]);
            listssh->_environ[n] = copy_info(nm_env, value);
            free(v_env);
            return;
        }
        free(v_env);
        n++;
    }
    listssh->_environ = _reallocdp(listssh->_environ, n, sizeof(char *) * (n + 2));
    listssh->_environ[n] = copy_info(name, value);
    listssh->_environ[n + 1] = NULL;
}

/**
 * _setenv - this function will compare env variables names with the name passed for us.
 * @listssh: lists relevant (env name and env value)
 * Return: 1 on success.
 */
int _setenv(lists_shell *listssh)
{
    if (listssh->args[1] == NULL || listssh->args[2] == NULL)
    {
        get_error(listssh, -1);
        return (1);
    }
    set_env(listssh->args[1], listssh->args[2], listssh);

    return (1);
}

/**
 * _unsetenv - this function will delete a environment variable for us.
 * @listssh: lists relevant (env name)
 * Return: 1 on success.
 */
int _unsetenv(lists_shell *listssh)
{
    char *v_env, *nm_env;

    int n, m, o;

    char **rlc_env;

    if (listssh->args[1] == NULL)
    {
        get_error(listssh, -1);
        return (1);
    }
    o = -1;
    n = 0;
    while (listssh->_environ[n])
    {
        v_env = _strdup(listssh->_environ[n]);
        nm_env = _strtok(v_env, "=");
        if (_strcmp(nm_env, listssh->args[1]) == 0)
            o = n;
        free(v_env);
        n++;
    }
    if (o == -1)
    {
        get_error(listssh, -1);
        return (1);
    }
    rlc_env = malloc(sizeof(char *) * (n));
    n = 0;
    m = 0;
    while (listssh->_environ[n])
    {
        if (n != o)
        {
            rlc_env[m] = listssh->_environ[n];
            m++;
        }
        n++;
    }
    rlc_env[m] = NULL;
    free(listssh->_environ[o]);
    free(listssh->_environ);
    listssh->_environ = rlc_env;
    return (1);
}
