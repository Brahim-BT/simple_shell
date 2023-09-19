#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int n;

    n = 0;
    while (nenv[n] != '=')
    {
        if (nenv[n] != name[n])
            return (0);
        n++;
    }
    return (n + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
    int n, mv;

    char *ptr_env;

    /* Initialize ptr_env value */
    ptr_env = NULL;
    mv = 0;
    /* Compare all environment variables */
    /* environ is declared in the header file */
    n = 0;
    while (_environ[n])
    {
        /* If name and env are equal */
        mv = cmp_env_name(_environ[n], name);
        if (mv)
        {
            ptr_env = _environ[n];
            break;
        }
        n++;
    }
    return (ptr_env + mv);
}

/**
 * _env - prints the evironment variables
 *
 * @listssh: lists relevant.
 * Return: 1 on success.
 */
int _env(lists_shell *listssh)
{
    int n, m;

    n = 0;
    while (listssh->_environ[n])
    {
        for (m = 0; listssh->_environ[n][m]; m++)
            ;
        write(STDOUT_FILENO, listssh->_environ[n], m);
        write(STDOUT_FILENO, "\n", 1);
        n++;
    }
    listssh->status = 0;
    return (1);
}
