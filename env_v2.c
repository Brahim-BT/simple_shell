#include "shell.h"

/**
 * _unsetenv - Remove an environment variable
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @my_var: the string env var property
 */
int _unsetenv(info_t *f, char *my_var)
{
	list_t *nd = f->env;

	size_t n = 0;

	char *ptr;

	if (!nd || !my_var)
		return (0);
	while (nd)
	{
		ptr = starts_with(nd->str, my_var);
		if (ptr && *ptr == '=')
		{
			f->env_changed = delete_node_at_index(&(f->env), n);
			n = 0;
			nd = f->env;
			continue;
		}
		nd = nd->next;
		n++;
	}
	return (f->env_changed);
}

/**
 * get_environ - returns the string array copy of our environ
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *f)
{
	if (!f->environ || f->env_changed)
	{
		f->environ = list_to_strings(f->env);
		f->env_changed = 0;
	}
	return (f->environ);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @my_var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *f, char *my_var, char *val)
{
	char *bfr = NULL;

	list_t *nd;

	char *ptr;

	if (!my_var || !val)
		return (0);
	bfr = malloc(_strlen(my_var) + _strlen(val) + 2);
	if (!bfr)
		return (1);
	_strcpy(bfr, my_var);
	_strcat(bfr, "=");
	_strcat(bfr, val);
	nd = f->env;
	while (nd)
	{
		ptr = starts_with(nd->str, my_var);
		if (ptr && *ptr == '=')
		{
			free(nd->str);
			nd->str = bfr;
			f->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(f->env), bfr, 0);
	free(bfr);
	f->env_changed = 1;
	return (0);
}
