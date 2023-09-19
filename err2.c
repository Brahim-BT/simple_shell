#include "main.h"

/**
 * error_env - this function will error message for env in get_env for us.
 * @listssh: lists relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(lists_shell *listssh)
{
	int l;
	
    char *err;
	
    char *ver_str;
	
    char *message;

	ver_str = aux_itoa(listssh->counter);
	message = ": Unable to add/remove from environment\n";
	l = _strlen(listssh->av[0]) + _strlen(ver_str);
	l += _strlen(listssh->args[0]) + _strlen(message) + 4;
	err = malloc(sizeof(char) * (l + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_strcpy(err, listssh->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, listssh->args[0]);
	_strcat(err, message);
	_strcat(err, "\0");
	free(ver_str);
	return (err);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @listssh: lists relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(lists_shell *listssh)
{
    char *err;
	
    char *ver_str;

	int l;
	
	ver_str = aux_itoa(listssh->counter);
	l = _strlen(listssh->av[0]) + _strlen(ver_str);
	l += _strlen(listssh->args[0]) + 24;
	err = malloc(sizeof(char) * (l + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_strcpy(err, listssh->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, listssh->args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(ver_str);
	return (err);
}
