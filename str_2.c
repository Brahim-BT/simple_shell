#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int cnt = 0, i, j;
	char *str, temp;
	while (cnt >= 0)
	{
		if (s[cnt] == '\0')
			break;
		cnt++;
	}
	str = s;
	for (i = 0; i < (cnt - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}

