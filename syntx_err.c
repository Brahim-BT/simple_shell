#include "main.h"

/**
 * rptd_chr - this function will count the repetitions of a char for us.
 * @input: the user input
 * @i: index
 * Return: repetitions
 */
int rptd_chr(char *input, int i)
{
	if (*(input - 1) == *input)
		return (rptd_chr(input - 1, i + 1));
	return (i);
}

/**
 * err_sp_op - finds syntax errors
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int err_sp_op(char *input, int i, char last)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (err_sp_op(input + 1, i + 1, last));
	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);
	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);
		if (last == '|')
		{
			c = rptd_chr(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}
	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);
		if (last == '&')
		{
			c = rptd_chr(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}
	return (err_sp_op(input + 1, i + 1, *input));
}

/**
 * frst_chr - this function will find index of the first char for us.
 * @input: input string
 * @i: index
 * Return: 1 or 0.
 */
int frst_chr(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * print_syntx_err - this function will print when a syntax error is found for us.
 * @listssh: lists structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: void
 */
void print_syntx_err(lists_shell *listssh, char *input, int i, int bool)
{
	int l;

	char *message, *message2, *message3, *error, *c;
	
	if (input[i] == ';')
	{
		if (bool == 0)
			message = (input[i + 1] == ';' ? ";;" : ";");
		else
			message = (input[i - 1] == ';' ? ";;" : ";");
	}
	if (input[i] == '|')
		message = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		message = (input[i + 1] == '&' ? "&&" : "&");
	message2 = ": Syntax error: \"";
	message3 = "\" unexpected\n";
	c = aux_itoa(listssh->counter);
	l = _strlen(listssh->av[0]) + _strlen(c);
	l += _strlen(message) + _strlen(message2) + _strlen(message3) + 2;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(c);
		return;
	}
	_strcpy(error, listssh->av[0]);
	_strcat(error, ": ");
	_strcat(error, c);
	_strcat(error, message2);
	_strcat(error, message);
	_strcat(error, message3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, l);
	free(error);
	free(c);
}

/**
 * syntx_err - intermediate function to
 * find and print a syntax error
 *
 * @listssh: lists structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int syntx_err(lists_shell *listssh, char *input)
{
	int n = 0;

	int f_chr = 0;
	
	int bgn = 0;

	f_chr = frst_chr(input, &bgn);
	if (f_chr == -1)
	{
		print_syntx_err(listssh, input, bgn, 0);
		return (1);
	}
	n = err_sp_op(input + bgn, 0, *(input + bgn));
	if (n != 0)
	{
		print_syntx_err(listssh, input, bgn + n, 1);
		return (1);
	}
	return (0);
}
