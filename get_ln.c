#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @f: parameter struct
 * @bfr: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *f, char **bfr, size_t *l)
{
    size_t l_ptr = 0;

    ssize_t x = 0;

    if (!*l) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)f->cmd_buf);*/
        free(*bfr);
        *bfr = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        x = getline(buf, &l_ptr, stdin);
#else
        x = _getline(f, bfr, &l_ptr);
#endif
        if (x > 0)
        {
            if ((*bfr)[x - 1] == '\n')
            {
                (*bfr)[x - 1] = '\0'; /* remove trailing newline */
                x--;
            }
            f->linecount_flag = 1;
            remove_comments(*bfr);
            build_history_list(f, *bfr, f->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *l = x;
                f->cmd_buf = bfr;
            }
        }
    }
    return (x);
}

/**
 * get_input - gets a line minus the newline
 * @f: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *f)
{
    ssize_t x = 0;

    static size_t m, n, l;

    static char *buf; /* the ';' command chain buffer */

    char **bfr_ptr = &(f->arg), *p;

    _putchar(BUF_FLUSH);
    x = input_buf(f, &buf, &l);
    if (x == -1) /* EOF */
        return (-1);
    if (l) /* we have commands left in the chain buffer */
    {
        n = m;       /* init new iterator to current buf position */
        p = buf + m; /* get pointer for return */
        check_chain(f, buf, &n, m, l);
        while (n < l) /* iterate to semicolon or end */
        {
            if (is_chain(f, buf, &n))
                break;
            n++;
        }
        m = n + 1;  /* increment past nulled ';'' */
        if (m >= l) /* reached end of buffer? */
        {
            m = l = 0; /* reset position and length */
            f->cmd_buf_type = CMD_NORM;
        }
        *bfr_ptr = p;        /* pass back pointer to current command position */
        return (_strlen(p)); /* return length of current command */
    }
    *bfr_ptr = buf; /* else not a chain, pass back buffer from _getline() */
    return (x);     /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @f: parameter struct
 * @buf: buffer
 * @m: size
 *
 * Return: x
 */
ssize_t read_buf(info_t *f, char *buf, size_t *m)
{
    ssize_t x = 0;

    if (*m)
        return (0);
    x = read(f->readfd, buf, READ_BUF_SIZE);
    if (x >= 0)
        *m = x;
    return (x);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

/**
 * _getline - gets the next line of input from STDIN
 * @f: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @l: size of preallocated ptr buffer if not NULL
 *
 * Return: something
 */
int _getline(info_t *f, char **ptr, size_t *l)
{
    
    static char buf[READ_BUF_SIZE];
    
    static size_t m, len;
    
    size_t o;
    
    ssize_t x = 0, something = 0;
    
    char *p = NULL, *new_ptr = NULL, *cc;

    p = *ptr;
    if (p && l)
        something = *l;
    if (m == len)
        m = len = 0;
    x = read_buf(f, buf, &len);
    if (x == -1 || (x == 0 && len == 0))
        return (-1);
    cc = _strchr(buf + m, '\n');
    o = cc ? 1 + (unsigned int)(cc - buf) : len;
    new_ptr = _realloc(p, something, something ? something + o : o + 1);
    if (!new_ptr) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);
    if (something)
        _strncat(new_ptr, buf + m, o - m);
    else
        _strncpy(new_ptr, buf + m, o - m + 1);
    something += o - m;
    m = o;
    p = new_ptr;
    if (l)
        *l = something;
    *ptr = p;
    return (something);
}
