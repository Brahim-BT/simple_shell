#include "shell.h"

/**
 * list_len - determines length of linked list
 * @header: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *header)
{
    size_t m = 0;

    while (header)
    {
        header = header->next;
        m++;
    }
    return (m);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    char **strings;

    size_t m = list_len(head), j;

    list_t *nd = head;

    char *string;

    if (!head || !m)
        return (NULL);
    strings = malloc(sizeof(char *) * (m + 1));
    if (!strings)
        return (NULL);
    for (m = 0; nd; nd = nd->next, m++)
    {
        string = malloc(_strlen(nd->str) + 1);
        if (!string)
        {
            for (j = 0; j < m; j++)
                free(strings[j]);
            free(strings);
            return (NULL);
        }
        string = _strcpy(string, nd->str);
        strings[m] = string;
    }
    strings[m] = NULL;
    return (strings);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @chars: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *nd, char *prefix, char chars)
{
    char *p = NULL;

    while (nd)
    {
        p = starts_with(nd->str, prefix);
        if (p && ((chars == -1) || (*p == chars)))
            return (nd);
        nd = nd->next;
    }
    return (NULL);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
    size_t m;

    for (m = 0; h; m++)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
    }
    return (m);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *nd)
{
    size_t m = 0;

    while (head)
    {
        if (head == nd)
            return (m);
        head = head->next;
        m++;
    }
    return (-1);
}
