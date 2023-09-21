#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @my_data_sh: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(data_shell *my_data_sh)
{
	char pwd[PATH_MAX];
	char *my_directory, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, my_data_sh);
	my_directory = my_data_sh->args[1];
	if (_strcmp(".", my_directory) == 0)
	{
		set_env("PWD", cp_pwd, my_data_sh);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, my_data_sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", my_data_sh);
	}
	my_data_sh->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @my_data_sh: data relevant (directories)
 * Return: no return
 */
void cd_to(data_shell *my_data_sh)
{
	char pwd[PATH_MAX];
	char *my_directory, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	my_directory = my_data_sh->args[1];
	if (chdir(my_directory) == -1)
	{
		get_error(my_data_sh, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, my_data_sh);

	cp_dir = _strdup(my_directory);
	set_env("PWD", cp_dir, my_data_sh);

	free(cp_pwd);
	free(cp_dir);

	my_data_sh->status = 0;

	chdir(my_directory);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @my_data_sh: data relevant (environ)
 * Return: no return
 */
void cd_previous(data_shell *my_data_sh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", my_data_sh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, my_data_sh);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, my_data_sh);
	else
		set_env("PWD", cp_oldpwd, my_data_sh);

	p_pwd = _getenv("PWD", my_data_sh->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	my_data_sh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @my_data_sh: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data_shell *my_data_sh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", my_data_sh->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, my_data_sh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(my_data_sh, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, my_data_sh);
	set_env("PWD", home, my_data_sh);
	free(p_pwd);
	my_data_sh->status = 0;
}
