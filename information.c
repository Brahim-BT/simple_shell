#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @f: struct address
 */
void clear_info(info_t *f)
{
	f->arg = NULL;
	f->argv = NULL;
	f->path = NULL;
	f->argc = 0;
}

/**
 * free_info - frees info_t struct fields
 * @f: struct address
 * @all_somthing: true if freeing all_somthing fields
 */
void free_info(info_t *f, int all_somthing)
{
	ffree(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (all_somthing)
	{
		if (!f->cmd_buf)
			free(f->arg);
		if (f->env)
			free_list(&(f->env));
		if (f->history)
			free_list(&(f->history));
		if (f->alias)
			free_list(&(f->alias));
		ffree(f->environ);
			f->environ = NULL;
		bfree((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * set_info - initializes info_t struct
 * @f: struct address
 * @av: argument vector
 */
void set_info(info_t *f, char **av)
{
	int m = 0;

	f->fname = av[0];
	if (f->arg)
	{
		f->argv = strtow(f->arg, " \t");
		if (!f->argv)
		{
			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _strdup(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (m = 0; f->argv && f->argv[m]; m++)
			;
		f->argc = m;
		replace_alias(f);
		replace_vars(f);
	}
}
