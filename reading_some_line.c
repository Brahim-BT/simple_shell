#include "main.h"

/**
 * read_line - reads the input string.
 *
 * @i_end_of_file: return value of getline function
 * Return: input string
 */
char *read_line(int *i_end_of_file)
{
	char *my_inpt = NULL;
	size_t my_bfr_sz = 0;

	*i_end_of_file = getline(&my_inpt, &my_bfr_sz, stdin);

	return (my_inpt);
}
