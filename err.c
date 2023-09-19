#include "main.h"

/**
 * get_error - this function will call the error according the builtin, syntax or permission for us.
 * @listssh: lists structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(lists_shell *listssh, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = error_env(listssh);
		break;
	case 126:
		err = error_path_126(listssh);
		break;
	case 127:
		err = error_not_found(listssh);
		break;
	case 2:
		if (_strcmp("exit", listssh->args[0]) == 0)
			err = error_exit_shell(listssh);
		else if (_strcmp("cd", listssh->args[0]) == 0)
			err = error_get_cd(listssh);
		break;
	}
	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}
	listssh->status = eval;
	return (eval);
}
