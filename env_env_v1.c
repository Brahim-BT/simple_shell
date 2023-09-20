#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @my_nenv: name of the environment variable
 * @my_nm: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *my_nenv, const char *my_nm)
{
    int m;

    for (m = 0; my_nenv[m] != '='; m++)
    {
        if (my_nenv[m] != my_nm[m])
            return (0);
    }
    return (m + 1);
}

/**
 * _env - prints the evironment variables
 *
 * @ssh_list: lists relevant.
 * Return: 1 on success.
 */
int _env(lists_shell *ssh_list)
{
    int m, n;

    for (m = 0; ssh_list->_environ[m]; m++)
    {
        for (n = 0; ssh_list->_environ[m][n]; n++)
            ;
        write(STDOUT_FILENO, ssh_list->_environ[m], n);
        write(STDOUT_FILENO, "\n", 1);
    }
    ssh_list->status = 0;
    return (1);
}

/**
 * _getenv - get an environment variable
 * @my_nm: name of the environment variable
 * @_environment: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *my_nm, char **_environment)
{
    int m, my_movement;

    char *my_ptr_env;

    /* Initialize ptr_env value */
    my_ptr_env = NULL;
    my_movement = 0;
    /* Compare all environment variables */
    /* environ is declared in the header file */
    for (m = 0; _environment[m]; m++)
    {
        /* If name and env are equal */
        my_movement = cmp_env_name(_environment[m], my_nm);
        if (my_movement)
        {
            my_ptr_env = _environment[m];
            break;
        }
    }
    return (my_ptr_env + my_movement);
}
