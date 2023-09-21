#include "main.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len(int n)
{
	unsigned int n1;
	int my_l = 1;

	if (n < 0)
	{
		my_l++;
		n1 = n * -1;
	}
	else
		n1 = n;
	while (n1 > 9)
	{
		my_l++;
		n1 = n1 / 10;
	}
	return (my_l);
}
/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int lenght = get_len(n);
	char *my_bfr;

	my_bfr = malloc(sizeof(char) * (lenght + 1));
	if (my_bfr == 0)
		return (NULL);
	*(my_bfr + lenght) = '\0';
	if (n < 0)
	{
		n1 = n * -1;
		my_bfr[0] = '-';
	}
	else
		n1 = n;
	lenght--;
	do
	{
		*(my_bfr + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	} while (n1 > 0);
	return (my_bfr);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int my_counter = 0, sz = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + my_counter) != '\0')
	{
		if (sz > 0 && (*(s + my_counter) < '0' || *(s + my_counter) > '9'))
			break;
		if (*(s + my_counter) == '-')
			pn *= -1;
		if ((*(s + my_counter) >= '0') && (*(s + my_counter) <= '9'))
		{
			if (sz > 0)
				m *= 10;
			sz++;
		}
		my_counter++;
	}
	for (i = my_counter - sz; i < my_counter; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
