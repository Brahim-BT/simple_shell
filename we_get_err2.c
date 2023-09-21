#include "main.h"

/**
 * error_env - my_err message for env in get_env.
 * @my_data_sh: data relevant (counter, arguments)
 * Return: my_err message.
 */
char *error_env(data_shell *my_data_sh)
{
	int my_l;
	char *my_err;
	char *ver_str;
	char *my_message;

	ver_str = aux_itoa(my_data_sh->counter);
	my_message = ": Unable to add/remove from environment\n";
	my_l = _strlen(my_data_sh->av[0]) + _strlen(ver_str);
	my_l += _strlen(my_data_sh->args[0]) + _strlen(my_message) + 4;
	my_err = malloc(sizeof(char) * (my_l + 1));
	if (my_err == 0)
	{
		free(my_err);
		free(ver_str);
		return (NULL);
	}
	_strcpy(my_err, my_data_sh->av[0]);
	_strcat(my_err, ": ");
	_strcat(my_err, ver_str);
	_strcat(my_err, ": ");
	_strcat(my_err, my_data_sh->args[0]);
	_strcat(my_err, my_message);
	_strcat(my_err, "\0");
	free(ver_str);
	return (my_err);
}
/**
 * error_path_126 - my_err message for path and failure denied permission.
 * @my_data_sh: data relevant (counter, arguments).
 *
 * Return: The my_err string.
 */
char *error_path_126(data_shell *my_data_sh)
{

	int my_l;

	char *ver_str;

	char *my_err;

	ver_str = aux_itoa(my_data_sh->counter);
	my_l = _strlen(my_data_sh->av[0]) + _strlen(ver_str);
	my_l += _strlen(my_data_sh->args[0]) + 24;
	my_err = malloc(sizeof(char) * (my_l + 1));
	if (my_err == 0)
	{
		free(my_err);
		free(ver_str);
		return (NULL);
	}
	_strcpy(my_err, my_data_sh->av[0]);
	_strcat(my_err, ": ");
	_strcat(my_err, ver_str);
	_strcat(my_err, ": ");
	_strcat(my_err, my_data_sh->args[0]);
	_strcat(my_err, ": Permission denied\n");
	_strcat(my_err, "\0");
	free(ver_str);
	return (my_err);
}
