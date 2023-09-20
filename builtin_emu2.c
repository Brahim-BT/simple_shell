#include "shell.h"

/**
 * unset_alias - sets alias to string
 * @f: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *f, char *s)
{
    int retro;

    char *pointer, cc;

    pointer = _strchr(s, '=');
    if (!pointer)
        return (1);
    cc = *pointer;
    *pointer = 0;
    retro = delete_node_at_index(&(f->alias),
                                 get_node_index(f->alias, node_starts_with(f->alias, s, -1)));
    *pointer = cc;
    return (retro);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @f: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *f)
{
    print_list(f->history);
    return (0);
}

/**
 * set_alias - sets alias to string
 * @f: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *f, char *s)
{
    char *ptr;

    ptr = _strchr(s, '=');
    if (!ptr)
        return (1);
    if (!*++ptr)
        return (unset_alias(f, s));
    unset_alias(f, s);
    return (add_node_end(&(f->alias), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nd: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *nd)
{
    char *ptr = NULL;

    char *alias = NULL;

    if (nd)
    {
        ptr = _strchr(nd->str, '=');
        for (alias = nd->str; alias <= ptr; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(ptr + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @f: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *f)
{
    list_t *nd = NULL;

    char *ptr = NULL;

    int n = 0;

    if (f->argc == 1)
    {
        nd = f->alias;
        while (nd)
        {
            print_alias(nd);
            nd = nd->next;
        }
        return (0);
    }
    n = 1;
    while (f->argv[n])
    {
        ptr = _strchr(f->argv[n], '=');
        if (ptr)
            set_alias(f, f->argv[n]);
        else
            print_alias(node_starts_with(f->alias, f->argv[n], '='));
        n++;
    }
    return (0);
}
