#include "main.h"

/**
 * get_len - Get the lenght of a number.
 * @nm: type int number.
 * Return: Lenght of a number.
 */
int get_len(int nm)
{
	unsigned int nm1;
	int lenght = 1;
	if (nm < 0)
	{
		lenght++;
		nm1 = nm * -1;
	}
	else
	{
		nm1 = nm;
	}
	while (nm1 > 9)
	{
		lenght++;
		nm1 = nm1 / 10;
	}
	return (lenght);
}
/**
 * aux_itoa - function converts int to string.
 * @nm: type int number
 * Return: String.
 */
char *aux_itoa(int nm)
{
	unsigned int nm1;
	int lenght = get_len(nm);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (nm < 0)
	{
		nm1 = nm * -1;
		buffer[0] = '-';
	}
	else
	{
		nm1 = nm;
	}

	lenght--;
	do {
		*(buffer + lenght) = (nm1 % 10) + '0';
		nm1 = nm1 / 10;
		lenght--;
	}
	while (nm1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;
	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}
	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}

