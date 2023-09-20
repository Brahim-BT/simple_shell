#include "shell.h"

/**
 * _eputchar - writes the character c to stderr
 * @chars: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char chars)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (chars == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (chars != BUF_FLUSH)
        buf[i++] = chars;
    return (1);
}

/**
 *_eputs - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
    int i = 0;

    if (!string)
        return;
    while (string[i] != '\0')
    {
        _eputchar(string[i]);
        i++;
    }
}

/**
 *_putsfd - prints an input string
 * @string: the string to be printed
 * @file_des: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int file_des)
{
    int n = 0;

    if (!string)
        return (0);
    while (*string)
    {
        n += _putfd(*string++, file_des);
    }
    return (n);
}

/**
 * _putfd - writes the character c to given fd
 * @chars: The character to print
 * @file_des: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char chars, int file_des)
{
    static char bfr[WRITE_BUF_SIZE];

    static int n;

    if (chars == BUF_FLUSH || n >= WRITE_BUF_SIZE)
    {
        write(file_des, bfr, n);
        n = 0;
    }
    if (chars != BUF_FLUSH)
        bfr[n++] = chars;
    return (1);
}
