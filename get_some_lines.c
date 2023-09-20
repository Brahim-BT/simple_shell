#include "main.h"

/**
 * bring_line - assigns the line var for get_line
 * @my_line_ptr: Buffer that store the input str
 * @my_bfr: str that is been called to line
 * @n: size of line
 * @w: size of buffer
 */
void bring_line(char **my_line_ptr, size_t *n, char *my_bfr, size_t w)
{
    if (*my_line_ptr == NULL)
    {
        if (w > BUFFERSIZE)
            *n = w;
        else
            *n = BUFFERSIZE;
        *my_line_ptr = my_bfr;
    }
    else if (*n < w)
    {
        if (w > BUFFERSIZE)
            *n = w;
        else
            *n = BUFFERSIZE;
        *my_line_ptr = my_bfr;
    }
    else
    {
        _strcpy(*my_line_ptr, my_bfr);
        free(my_bfr);
    }
}
/**
 * get_line - Read inpt from stream
 * @my_line_ptr: buffer that stores the input
 * @n: size of lineptr
 * @my_strm: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **my_line_ptr, size_t *n, FILE *my_strm)
{

    int m;

    static ssize_t my_inpt;

    ssize_t my_rtvl;

    char *my_bfr;

    char t = 'z';

    if (my_inpt == 0)
        fflush(my_strm);
    else
        return (-1);
    my_inpt = 0;
    my_bfr = malloc(sizeof(char) * BUFFERSIZE);
    if (my_bfr == 0)
        return (-1);
    while (t != '\n')
    {
        m = read(STDIN_FILENO, &t, 1);
        if (m == -1 || (m == 0 && my_inpt == 0))
        {
            free(my_bfr);
            return (-1);
        }
        if (m == 0 && my_inpt != 0)
        {
            my_inpt++;
            break;
        }
        if (my_inpt >= BUFFERSIZE)
            my_bfr = _realloc(my_bfr, my_inpt, my_inpt + 1);
        my_bfr[my_inpt] = t;
        my_inpt++;
    }
    my_bfr[my_inpt] = '\0';
    bring_line(my_line_ptr, n, my_bfr, my_inpt);
    my_rtvl = my_inpt;
    if (m != 0)
        my_inpt = 0;
    return (my_rtvl);
}
