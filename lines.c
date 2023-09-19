#include "main.h"

/**
 * bring_line - this function will assign the line var for get_line for us.
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
    if (*lineptr == NULL)
    {
        if (j > BUFFERSIZE)
            *n = j;
        else
            *n = BUFFERSIZE;
        *lineptr = buffer;
    }
    else if (*n < j)
    {
        if (j > BUFFERSIZE)
            *n = j;
        else
            *n = BUFFERSIZE;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}
/**
 * get_line - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
    ssize_t rtvl;

    static ssize_t inpt;

    char ch = 'z';

    char *bfr;

    int n;

    if (inpt == 0)
        fflush(stream);
    else
        return (-1);
    inpt = 0;
    bfr = malloc(sizeof(char) * BUFFERSIZE);
    if (bfr == 0)
        return (-1);
    while (ch != '\n')
    {
        n = read(STDIN_FILENO, &ch, 1);
        if (n == -1 || (n == 0 && inpt == 0))
        {
            free(bfr);
            return (-1);
        }
        if (n == 0 && inpt != 0)
        {
            inpt++;
            break;
        }
        if (inpt >= BUFFERSIZE)
            bfr = _realloc(bfr, inpt, inpt + 1);
        bfr[inpt] = ch;
        inpt++;
    }
    bfr[inpt] = '\0';
    bring_line(lineptr, n, bfr, inpt);
    rtvl = inpt;
    if (n != 0)
        inpt = 0;
    return (rtvl);
}
