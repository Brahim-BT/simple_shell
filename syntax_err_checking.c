#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @my_inpt: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *my_inpt, int i)
{
	if (*(my_inpt - 1) == *my_inpt)
		return (repeated_char(my_inpt - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @my_inpt: input string
 * @m: index
 * @my_lst: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *my_inpt, int m, char my_lst)
{
	int full_counter;

	full_counter = 0;
	if (*my_inpt == '\0')
		return (0);

	if (*my_inpt == ' ' || *my_inpt == '\t')
		return (error_sep_op(my_inpt + 1, m + 1, my_lst));

	if (*my_inpt == ';')
		if (my_lst == '|' || my_lst == '&' || my_lst == ';')
			return (m);

	if (*my_inpt == '|')
	{
		if (my_lst == ';' || my_lst == '&')
			return (m);

		if (my_lst == '|')
		{
			full_counter = repeated_char(my_inpt, 0);
			if (full_counter == 0 || full_counter > 1)
				return (m);
		}
	}

	if (*my_inpt == '&')
	{
		if (my_lst == ';' || my_lst == '|')
			return (m);

		if (my_lst == '&')
		{
			full_counter = repeated_char(my_inpt, 0);
			if (full_counter == 0 || full_counter > 1)
				return (m);
		}
	}

	return (error_sep_op(my_inpt + 1, m + 1, *my_inpt));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *i)
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
 * print_syntax_error - prints when a syntax error is found
 *
 * @my_data_sh: data structure
 * @input: input string
 * @m: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(data_shell *my_data_sh, char *input, int m, int bool)
{
	char *my_message, *my_message2, *my_message3, *some_err, *full_counter;

	int my_l;

	if (input[m] == ';')
	{
		if (bool == 0)
			my_message = (input[m + 1] == ';' ? ";;" : ";");
		else
			my_message = (input[m - 1] == ';' ? ";;" : ";");
	}
	if (input[m] == '|')
		my_message = (input[m + 1] == '|' ? "||" : "|");
	if (input[m] == '&')
		my_message = (input[m + 1] == '&' ? "&&" : "&");
	my_message2 = ": Syntax error: \"";
	my_message3 = "\" unexpected\n";
	full_counter = aux_itoa(my_data_sh->counter);
	my_l = _strlen(my_data_sh->av[0]) + _strlen(full_counter);
	my_l += _strlen(my_message) + _strlen(my_message2) + _strlen(my_message3) + 2;
	some_err = malloc(sizeof(char) * (my_l + 1));
	if (some_err == 0)
	{
		free(full_counter);
		return;
	}
	_strcpy(some_err, my_data_sh->av[0]);
	_strcat(some_err, ": ");
	_strcat(some_err, full_counter);
	_strcat(some_err, my_message2);
	_strcat(some_err, my_message);
	_strcat(some_err, my_message3);
	_strcat(some_err, "\0");
	write(STDERR_FILENO, some_err, my_l);
	free(some_err);
	free(full_counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @my_data_sh: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *my_data_sh, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(my_data_sh, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(my_data_sh, input, begin + i, 1);
		return (1);
	}

	return (0);
}
