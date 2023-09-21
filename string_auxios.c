#include "main.h"

/**
 * _strcat - concatenate two strings
 * @destination: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *destination, const char *src)
{
	int m;

	int n;

	for (m = 0; destination[m] != '\0'; m++)
		;
	for (n = 0; src[n] != '\0'; n++)
	{
		destination[m] = src[n];
		m++;
	}
	destination[m] = '\0';
	return (destination);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @destination: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *destination, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		destination[a] = src[a];
	}
	destination[a] = '\0';
	return (destination);
}
/**
 * _strcmp - Function that compares two strings.
 * @string1: type str compared
 * @string2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *string1, char *string2)
{
	int m;

	for (m = 0; string1[m] == string2[m] && string1[m]; m++)
		;
	if (string1[m] > string2[m])
		return (1);
	if (string1[m] < string2[m])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int m, n, bool;

	for (m = 0; *(s + m) != '\0'; m++)
	{
		bool = 1;
		for (n = 0; *(accept + n) != '\0'; n++)
		{
			if (*(s + m) == *(accept + n))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (m);
}
