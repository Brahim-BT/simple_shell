#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @f: the parameter struct
 * @bfr: the char buffer
 * @ptr: address of current position in bfr
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *f, char *bfr, size_t *ptr)
{
    size_t j = *ptr;

    if (bfr[j] == '|' && bfr[j + 1] == '|')
    {
        bfr[j] = 0;
        j++;
        f->cmd_buf_type = CMD_OR;
    }
    else if (bfr[j] == '&' && bfr[j + 1] == '&')
    {
        bfr[j] = 0;
        j++;
        f->cmd_buf_type = CMD_AND;
    }
    else if (bfr[j] == ';') /* found end of this command */
    {
        bfr[j] = 0; /* replace semicolon with null */
        f->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *ptr = j;
    return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @f: the parameter struct
 * @bfr: the char buffer
 * @ptr: address of current position in bfr
 * @n: starting position in bfr
 * @l: length of bfr
 *
 * Return: Void
 */
void check_chain(info_t *f, char *bfr, size_t *ptr, size_t n, size_t l)
{
    size_t j = *ptr;

    if (f->cmd_buf_type == CMD_AND)
    {
        if (f->status)
        {
            bfr[n] = 0;
            j = l;
        }
    }
    if (f->cmd_buf_type == CMD_OR)
    {
        if (!f->status)
        {
            bfr[n] = 0;
            j = l;
        }
    }
    *ptr = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @f: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *f)
{
    char *ptr;

    list_t *nd;

    int n;

    n = 0;
    while (n < 10)
    {
        nd = node_starts_with(f->alias, f->argv[0], '=');
        if (!nd)
            return (0);
        free(f->argv[0]);
        ptr = _strchr(nd->str, '=');
        if (!ptr)
            return (0);
        ptr = _strdup(ptr + 1);
        if (!ptr)
            return (0);
        f->argv[0] = ptr;
        n++;
    }
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @f: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *f)
{
    int n = 0;
    list_t *nd;

    n = 0;
    while (f->argv[n])
    {
        if (f->argv[n][0] != '$' || !f->argv[n][1])
            continue;
        if (!_strcmp(f->argv[n], "$?"))
        {
            replace_string(&(f->argv[n]),
                           _strdup(convert_number(f->status, 10, 0)));
            continue;
        }
        if (!_strcmp(f->argv[n], "$$"))
        {
            replace_string(&(f->argv[n]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        nd = node_starts_with(f->env, &f->argv[n][1], '=');
        if (nd)
        {
            replace_string(&(f->argv[n]),
                           _strdup(_strchr(nd->str, '=') + 1));
            continue;
        }
        replace_string(&f->argv[n], _strdup(""));
        n++;
    }
    return (0);
}

/**
 * replace_string - replaces string
 * @o: address of old string
 * @nw: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **o, char *nw)
{
    free(*o);
    *o = nw;
    return (1);
}
