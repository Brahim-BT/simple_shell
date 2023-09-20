#include "main.h"

/**
 * free_lists - frees lists structure
 *
 * @listssh: lists structure
 * Return: no return
 */
 
 
void free_lists(lists_shell *listssh)
{
	unsigned int j;

	for (j = 0; listssh->_environ[j]; j++)
	{
		free(listssh->_environ[j]);
	}

	free(listssh->_environ);
	free(listssh->pid);
}

/**
 * set_lists - Initialize lists structure
 *
 * @listssh: lists structure
 * @av: argument vector
 * Return: no return
 */
 
 
void set_lists(lists_shell *listssh, char **av)
{
	unsigned int j;

	listssh->av = av;
	listssh->input = NULL;
	listssh->args = NULL;
	listssh->status = 0;
	listssh->counter = 1;

	for (j = 0; environ[j]; j++)
		;

	listssh->_environ = malloc(sizeof(char *) * (j + 1));

	for (j = 0; environ[j]; j++)
	{
		listssh->_environ[j] = _strdup(environ[j]);
	}

	listssh->_environ[j] = NULL;
	listssh->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	lists_shell listssh;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_lists(&listssh, av);
	shell_loop(&listssh);
	free_lists(&listssh);
	if (listssh.status < 0)
		return (255);
	return (listssh.status);
}

