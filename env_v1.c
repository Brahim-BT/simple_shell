#include "shell.h"

/**
 * _myenv - prints the current environment
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *f)
{
	print_list_str(f->env);
	return (0);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *f)
{
	if (f->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}

/**
 * _getenv - gets the value of an environ variable
 * @f: Structure containing potential arguments. Used to maintain
 * @nm: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *f, const char *nm)
{
	char *ptr;

	list_t *nd = f->env;
    
	while (nd)
	{
		ptr = starts_with(nd->str, nm);
		if (ptr && *ptr)
			return (ptr);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * _myunsetenv - Remove an environment variable
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *f)
{
	int n;

	if (f->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= f->argc; n++)
		_unsetenv(f, f->argv[n]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *f)
{
	list_t *nd = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&nd, environ[n], 0);
	f->env = nd;
	return (0);
}
