#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int full_counter = 0, m, n;

	char *my_str, my_temp;

	while (full_counter >= 0)
	{
		if (s[full_counter] == '\0')
			break;
		full_counter++;
	}
	my_str = s;
	for (m = 0; m < (full_counter - 1); m++)
	{
		for (n = m + 1; n > 0; n--)
		{
			my_temp = *(my_str + n);
			*(my_str + n) = *(my_str + (n - 1));
			*(my_str + (n - 1)) = my_temp;
		}
	}
}
