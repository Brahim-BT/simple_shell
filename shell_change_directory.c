#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @my_data_sh: data relevant
 * Return: 1 on success
 */
int cd_shell(data_shell *my_data_sh)
{
	char *my_directory;

	int is_hm, is_hm2, is_d_sh;

	my_directory = my_data_sh->args[1];
	if (my_directory != NULL)
	{
		is_hm = _strcmp("$HOME", my_directory);
		is_hm2 = _strcmp("~", my_directory);
		is_d_sh = _strcmp("--", my_directory);
	}
	if (my_directory == NULL || !is_hm || !is_hm2 || !is_d_sh)
	{
		cd_to_home(my_data_sh);
		return (1);
	}
	if (_strcmp("-", my_directory) == 0)
	{
		cd_previous(my_data_sh);
		return (1);
	}
	if (_strcmp(".", my_directory) == 0 || _strcmp("..", my_directory) == 0)
	{
		cd_dot(my_data_sh);
		return (1);
	}
	cd_to(my_data_sh);
	return (1);
}
