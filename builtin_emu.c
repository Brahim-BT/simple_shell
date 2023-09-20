#include "shell.h"

/**
 * _myexit - this function will exit the shell for us.
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if f.argv[0] != "exit"
 */
int _myexit(info_t *f)
{
    int extchk;

    if (f->argv[1]) /* If there is an exit arguement */
    {
        extchk = _erratoi(f->argv[1]);
        if (extchk == -1)
        {
            f->status = 2;
            print_error(f, "Illegal number: ");
            _eputs(f->argv[1]);
            _eputchar('\n');
            return (1);
        }
        f->err_num = _erratoi(f->argv[1]);
        return (-2);
    }
    f->err_num = -1;
    return (-2);
}

/**
 * _mycd - this function will change the current directory of the process for us.
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: 0
 */
int _mycd(info_t *f)
{
    int chdirectory_ret;

    char *something, *directory, bfr[1024];

    something = getcwd(bfr, 1024);
    if (!something)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!f->argv[1])
    {
        directory = _getenv(f, "HOME=");
        if (!directory)
            chdirectory_ret = /* TODO: what should this be? */
                chdir((directory = _getenv(f, "PWD=")) ? directory : "/");
        else
            chdirectory_ret = chdir(directory);
    }
    else if (_strcmp(f->argv[1], "-") == 0)
    {
        if (!_getenv(f, "OLDPWD="))
        {
            _puts(something);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(f, "OLDPWD=")), _putchar('\n');
        chdirectory_ret = /* TODO: what should this be? */
            chdir((directory = _getenv(f, "OLDPWD=")) ? directory : "/");
    }
    else
        chdirectory_ret = chdir(f->argv[1]);
    if (chdirectory_ret == -1)
    {
        print_error(f, "can't cd to ");
        _eputs(f->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(f, "OLDPWD", _getenv(f, "PWD="));
        _setenv(f, "PWD", getcwd(bfr, 1024));
    }
    return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *f)
{
    char **argument_array;

    argument_array = f->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*argument_array); /* temp att_unused workaround */
    return (0);
}
