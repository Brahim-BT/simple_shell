#include "main.h"

/**
 * exit_shell - this function will exit the shell for us.
 * @listssh: lists relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(lists_shell *listssh)
{
	unsigned int sts;
	
    int is_dgt;
	
    int str_l;
	
    int bg_n;

	if (listssh->args[1] != NULL)
	{
		sts = _atoi(listssh->args[1]);
		is_dgt = _isdigit(listssh->args[1]);
		str_l = _strlen(listssh->args[1]);
		bg_n = sts > (unsigned int)INT_MAX;
		if (!is_dgt || str_l > 10 || bg_n)
		{
			get_error(listssh, 2);
			listssh->status = 2;
			return (1);
		}
		listssh->status = (sts % 256);
	}
	return (0);
}
