#include "main.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @my_str: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *my_str)
{
	char *my_new;
	size_t my_l;

	my_l = _strlen(my_str);
	my_new = malloc(sizeof(char) * (my_l + 1));
	if (my_new == NULL)
		return (NULL);
	_memcpy(my_new, my_str, my_l + 1);
	return (my_new);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int m, n, o;

	for (m = 0, o = 0; str[m]; m++)
	{
		for (n = 0; delim[n]; n++)
		{
			if (str[m] == delim[n])
			{
				o++;
				break;
			}
		}
	}
	if (m == o)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *my_spliter, *end_string;
	
	char *strat_string;
	
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		my_spliter = str; /*Store first address*/
		i = _strlen(str);
		end_string = &str[i]; /*Store last address*/
	}
	strat_string = my_spliter;
	if (strat_string == end_string) /*Reaching the end*/
		return (NULL);
	for (bool = 0; *my_spliter; my_spliter++)
	{
		/*Breaking loop finding the next token*/
		if (my_spliter != strat_string)
			if (*my_spliter && *(my_spliter - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*my_spliter == delim[i])
			{
				*my_spliter = '\0';
				if (my_spliter == strat_string)
					strat_string++;
				break;
			}
		}
		if (bool == 0 && *my_spliter) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (strat_string);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
