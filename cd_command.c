#include "main.h"
/**
 * cd_shell - this function will change from the current directory for us.
 * @listssh: list of ssh
 * Return: 1
 */
int cd_command(lists_shell *listssh)
{
	int hm, hm2, dsh;

	char *directory;

	directory = listssh->args[1];
	if (directory != NULL)
	{
		dsh = _strcmp("--", directory);
		hm = _strcmp("$HOME", directory);
		hm2 = _strcmp("~", directory);
	}
	if (directory == NULL || !hm || !hm2 || !dsh)
	{
		cd_hm(listssh);
		return (1);
	}
	if (_strcmp("-", directory) == 0)
	{
		cd_pre(listssh);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_d(listssh);
		return (1);
	}
	cd_t(listssh);
	return (1);
}
