#include "main.h"

/**
 * exec_line - finds builtins and commands
 *
 * @my_data_sh: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_shell *my_data_sh)
{
	int (*builtin)(data_shell *my_data_sh);

	if (my_data_sh->args[0] == NULL)
		return (1);

	builtin = get_builtin(my_data_sh->args[0]);

	if (builtin != NULL)
		return (builtin(my_data_sh));

	return (cmd_exec(my_data_sh));
}
