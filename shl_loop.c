#include "main.h"


/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
 
char *without_comment(char *in)
{
    
	int j, up_to;

	up_to = 0;
	for (j = 0; in[j]; j++)
	{
		if (in[j] == '#')
		{
			if (j == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[j - 1] == ' ' || in[j - 1] == '\t' || in[j - 1] == ';')
				up_to = j;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, j, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}



/**
 * shell_loop - Loop of shell
 * @listssh: lists relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(lists_shell *listssh)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(listssh, input) == 1)
			{
				listssh->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, listssh);
			loop = split_commands(listssh, input);
			listssh->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

