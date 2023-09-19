#include "main.h"

/**
 * cd_d - the function will changes to the parent directory for us.
 * @listssh: lists of ssh (environ)
 * Return: no return
 */
void cd_d(lists_shell *listssh)
{
    char *directory, *cpwd, *cp_strk_pwd;

    char pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    cpwd = _strdup(pwd);
    set_env("OLDPWD", cpwd, listssh);
    directory = listssh->args[1];
    if (_strcmp(".", directory) == 0)
    {
        set_env("PWD", cpwd, listssh);
        free(cpwd);
        return;
    }
    if (_strcmp("/", cpwd) == 0)
    {
        free(cpwd);
        return;
    }
    cp_strk_pwd = cpwd;
    rev_string(cp_strk_pwd);
    cp_strk_pwd = _strtok(cp_strk_pwd, "/");
    if (cp_strk_pwd != NULL)
    {
        cp_strk_pwd = _strtok(NULL, "\0");
        if (cp_strk_pwd != NULL)
            rev_string(cp_strk_pwd);
    }
    if (cp_strk_pwd != NULL)
    {
        chdir(cp_strk_pwd);
        set_env("PWD", cp_strk_pwd, listssh);
    }
    else
    {
        chdir("/");
        set_env("PWD", "/", listssh);
    }
    listssh->status = 0;
    free(cpwd);
}

/**
 * cd_t - this function will changes to a directory given for us.
 * @listssh: lists of ssh (directories)
 * Return: void
 */
void cd_t(lists_shell *listssh)
{
    char *directory, *cpwd, *cp_directory;

    char pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    directory = listssh->args[1];
    if (chdir(directory) == -1)
    {
        get_error(listssh, 2);
        return;
    }
    cpwd = _strdup(pwd);
    set_env("OLDPWD", cpwd, listssh);
    cp_directory = _strdup(directory);
    set_env("PWD", cp_directory, listssh);
    free(cpwd);
    free(cp_directory);
    listssh->status = 0;
    chdir(directory);
}

/**
 * cd_pre - this function will change to the previous directory for us.
 * @listssh: lists of ssh (environ)
 * Return: void
 */
void cd_pre(lists_shell *listssh)
{
    char *p_pwd, *p_oldpwd, *cpwd, *cp_oldpwd;

    char pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    cpwd = _strdup(pwd);
    p_oldpwd = _getenv("OLDPWD", listssh->_environ);
    if (p_oldpwd == NULL)
        cp_oldpwd = cpwd;
    else
        cp_oldpwd = _strdup(p_oldpwd);
    set_env("OLDPWD", cpwd, listssh);
    if (chdir(cp_oldpwd) == -1)
        set_env("PWD", cpwd, listssh);
    else
        set_env("PWD", cp_oldpwd, listssh);
    p_pwd = _getenv("PWD", listssh->_environ);
    write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
    write(STDOUT_FILENO, "\n", 1);
    free(cpwd);
    if (p_oldpwd)
        free(cp_oldpwd);
    listssh->status = 0;
    chdir(p_pwd);
}

/**
 * cd_hm - this function will changes to home directory for us.
 * @listssh: lists of ssh (environ)
 * Return: void
 */
void cd_hm(lists_shell *listssh)
{
    char pwd[PATH_MAX];

    char *p_pwd, *hm;

    getcwd(pwd, sizeof(pwd));
    p_pwd = _strdup(pwd);
    hm = _getenv("HOME", listssh->_environ);
    if (hm == NULL)
    {
        set_env("OLDPWD", p_pwd, listssh);
        free(p_pwd);
        return;
    }
    if (chdir(hm) == -1)
    {
        get_error(listssh, 2);
        free(p_pwd);
        return;
    }
    set_env("OLDPWD", p_pwd, listssh);
    set_env("PWD", hm, listssh);
    free(p_pwd);
    listssh->status = 0;
}
