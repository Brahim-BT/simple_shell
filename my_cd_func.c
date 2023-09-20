#include "main.h"

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @ssh_list: lists relevant (directories)
 * Return: no return
 */
void cd_to(lists_shell *ssh_list)
{
    char pwd[PATH_MAX];

    char *my_dir, *my_cp_pwd, *my_cp_dir;

    getcwd(pwd, sizeof(pwd));
    my_dir = ssh_list->args[1];
    if (chdir(my_dir) == -1)
    {
        get_error(ssh_list, 2);
        return;
    }
    my_cp_pwd = _strdup(pwd);
    set_env("OLDPWD", my_cp_pwd, ssh_list);
    my_cp_dir = _strdup(my_dir);
    set_env("PWD", my_cp_dir, ssh_list);
    free(my_cp_pwd);
    free(my_cp_dir);
    ssh_list->status = 0;
    chdir(my_dir);
}

/**
 * cd_dot - changes to the parent directory
 *
 * @ssh_list: lists relevant (environ)
 *
 * Return: no return
 */
void cd_dot(lists_shell *ssh_list)
{
    char my_pwd[PATH_MAX];

    char *my_directory, *cp_pwd, *cp_strk_pwd;

    getcwd(my_pwd, sizeof(my_pwd));
    cp_pwd = _strdup(my_pwd);
    set_env("OLDPWD", cp_pwd, ssh_list);
    my_directory = ssh_list->args[1];
    if (_strcmp(".", my_directory) == 0)
    {
        set_env("PWD", cp_pwd, ssh_list);
        free(cp_pwd);
        return;
    }
    if (_strcmp("/", cp_pwd) == 0)
    {
        free(cp_pwd);
        return;
    }
    cp_strk_pwd = cp_pwd;
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
        set_env("PWD", cp_strk_pwd, ssh_list);
    }
    else
    {
        chdir("/");
        set_env("PWD", "/", ssh_list);
    }
    ssh_list->status = 0;
    free(cp_pwd);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @ssh_list: lists relevant (environ)
 * Return: no return
 */
void cd_previous(lists_shell *ssh_list)
{
    char pwd[PATH_MAX];

    char *my_p_pwd, *my_p_oldpwd, *my_cp_pwd, *my_cp_oldpwd;

    getcwd(pwd, sizeof(pwd));
    my_cp_pwd = _strdup(pwd);
    my_p_oldpwd = _getenv("OLDPWD", ssh_list->_environ);
    if (my_p_oldpwd == NULL)
        my_cp_oldpwd = my_cp_pwd;
    else
        my_cp_oldpwd = _strdup(my_p_oldpwd);
    set_env("OLDPWD", my_cp_pwd, ssh_list);
    if (chdir(my_cp_oldpwd) == -1)
        set_env("PWD", my_cp_pwd, ssh_list);
    else
        set_env("PWD", my_cp_oldpwd, ssh_list);
    my_p_pwd = _getenv("PWD", ssh_list->_environ);
    write(STDOUT_FILENO, my_p_pwd, _strlen(my_p_pwd));
    write(STDOUT_FILENO, "\n", 1);
    free(my_cp_pwd);
    if (my_p_oldpwd)
        free(my_cp_oldpwd);
    ssh_list->status = 0;
    chdir(my_p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @ssh_list: lists relevant (environ)
 * Return: no return
 */
void cd_to_home(lists_shell *ssh_list)
{
    char *my_p_pwd, *my_home;

    char pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    my_p_pwd = _strdup(pwd);
    my_home = _getenv("HOME", ssh_list->_environ);
    if (my_home == NULL)
    {
        set_env("OLDPWD", my_p_pwd, ssh_list);
        free(my_p_pwd);
        return;
    }
    if (chdir(my_home) == -1)
    {
        get_error(ssh_list, 2);
        free(my_p_pwd);
        return;
    }
    set_env("OLDPWD", my_p_pwd, ssh_list);
    set_env("PWD", my_home, ssh_list);
    free(my_p_pwd);
    ssh_list->status = 0;
}
