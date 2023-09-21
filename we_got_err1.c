#include "main.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @my_data_sh: data relevant (directory)
 * @my_message: message to print
 * @my_err: output message
 * @my_ver_string: counter lines
 * Return: error message
 */
char *strcat_cd(data_shell *my_data_sh, char *my_message, char *my_err, char *my_ver_string)
{
	char *illegal_flag;

	_strcpy(my_err, my_data_sh->av[0]);
	_strcat(my_err, ": ");
	_strcat(my_err, my_ver_string);
	_strcat(my_err, ": ");
	_strcat(my_err, my_data_sh->args[0]);
	_strcat(my_err, my_message);
	if (my_data_sh->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = my_data_sh->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(my_err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(my_err, my_data_sh->args[1]);
	}
	_strcat(my_err, "\n");
	_strcat(my_err, "\0");
	return (my_err);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @my_data_sh: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd(data_shell *my_data_sh)
{
	int my_l, my_l_id;

	char *my_err, *ver_str, *my_message;

	ver_str = aux_itoa(my_data_sh->counter);
	if (my_data_sh->args[1][0] == '-')
	{
		my_message = ": Illegal option ";
		my_l_id = 2;
	}
	else
	{
		my_message = ": can't cd to ";
		my_l_id = _strlen(my_data_sh->args[1]);
	}
	my_l = _strlen(my_data_sh->av[0]) + _strlen(my_data_sh->args[0]);
	my_l += _strlen(ver_str) + _strlen(my_message) + my_l_id + 5;
	my_err = malloc(sizeof(char) * (my_l + 1));
	if (my_err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	my_err = strcat_cd(my_data_sh, my_message, my_err, ver_str);
	free(ver_str);
	return (my_err);
}

/**
 * error_not_found - generic error message for command not found
 * @my_data_sh: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(data_shell *my_data_sh)
{
	int my_l;
	char *my_err;
	char *my_ver_string;

	my_ver_string = aux_itoa(my_data_sh->counter);
	my_l = _strlen(my_data_sh->av[0]) + _strlen(my_ver_string);
	my_l += _strlen(my_data_sh->args[0]) + 16;
	my_err = malloc(sizeof(char) * (my_l + 1));
	if (my_err == 0)
	{
		free(my_err);
		free(my_ver_string);
		return (NULL);
	}
	_strcpy(my_err, my_data_sh->av[0]);
	_strcat(my_err, ": ");
	_strcat(my_err, my_ver_string);
	_strcat(my_err, ": ");
	_strcat(my_err, my_data_sh->args[0]);
	_strcat(my_err, ": not found\n");
	_strcat(my_err, "\0");
	free(my_ver_string);
	return (my_err);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @my_data_sh: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *my_data_sh)
{
	int my_l;
	char *my_err;
	char *my_ver_string;

	my_ver_string = aux_itoa(my_data_sh->counter);
	my_l = _strlen(my_data_sh->av[0]) + _strlen(my_ver_string);
	my_l += _strlen(my_data_sh->args[0]) + _strlen(my_data_sh->args[1]) + 23;
	my_err = malloc(sizeof(char) * (my_l + 1));
	if (my_err == 0)
	{
		free(my_ver_string);
		return (NULL);
	}
	_strcpy(my_err, my_data_sh->av[0]);
	_strcat(my_err, ": ");
	_strcat(my_err, my_ver_string);
	_strcat(my_err, ": ");
	_strcat(my_err, my_data_sh->args[0]);
	_strcat(my_err, ": Illegal number: ");
	_strcat(my_err, my_data_sh->args[1]);
	_strcat(my_err, "\n\0");
	free(my_ver_string);

	return (my_err);
}
