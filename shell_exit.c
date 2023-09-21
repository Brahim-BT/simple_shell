#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @my_data_sh: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *my_data_sh)
{
	unsigned int my_status;
	int is_it_digit;
	int my_string_l;
	int my_bg_num;

	if (my_data_sh->args[1] != NULL)
	{
		my_status = _atoi(my_data_sh->args[1]);
		is_it_digit = _isdigit(my_data_sh->args[1]);
		my_string_l = _strlen(my_data_sh->args[1]);
		my_bg_num = my_status > (unsigned int)INT_MAX;
		if (!is_it_digit || my_string_l > 10 || my_bg_num)
		{
			get_error(my_data_sh, 2);
			my_data_sh->status = 2;
			return (1);
		}
		my_data_sh->status = (my_status % 256);
	}
	return (0);
}
