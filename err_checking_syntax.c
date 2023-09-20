#include "main.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @my_inpt: input string
 * @m: index
 * Return: repetitions
 */
int repeated_char(char *my_inpt, int m)
{
    if (*(my_inpt - 1) == *my_inpt)
        return (repeated_char(my_inpt - 1, m + 1));
    return (m);
}

/**
 * first_char - finds index of the first char
 *
 * @my_inpt: input string
 * @m: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *my_inpt, int *m)
{
    for (*m = 0; my_inpt[*m]; *m += 1)
    {
        if (my_inpt[*m] == ' ' || my_inpt[*m] == '\t')
            continue;
        if (my_inpt[*m] == ';' || my_inpt[*m] == '|' || my_inpt[*m] == '&')
            return (-1);
        break;
    }
    return (0);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @my_inpt: input string
 * @m: index
 * @my_lst: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *my_inpt, int m, char my_lst)
{
    int my_count;

    my_count = 0;
    if (*my_inpt == '\0')
        return (0);
    if (*my_inpt == ' ' || *my_inpt == '\t')
        return (error_sep_op(my_inpt + 1, m + 1, my_lst));
    if (*my_inpt == ';')
        if (my_lst == '|' || my_lst == '&' || my_lst == ';')
            return (m);
    if (*my_inpt == '|')
    {
        if (my_lst == ';' || my_lst == '&')
            return (m);
        if (my_lst == '|')
        {
            my_count = repeated_char(my_inpt, 0);
            if (my_count == 0 || my_count > 1)
                return (m);
        }
    }
    if (*my_inpt == '&')
    {
        if (my_lst == ';' || my_lst == '|')
            return (m);
        if (my_lst == '&')
        {
            my_count = repeated_char(my_inpt, 0);
            if (my_count == 0 || my_count > 1)
                return (m);
        }
    }
    return (error_sep_op(my_inpt + 1, m + 1, *my_inpt));
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @ssh_list: lists structure
 * @my_inpt: input string
 * @m: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(lists_shell *ssh_list, char *my_inpt, int m, int bool)
{
    char *my_message, *my_massage2, *my_message3, *error, *full_counter;

    int l;

    if (my_inpt[m] == ';')
    {
        if (bool == 0)
            my_message = (my_inpt[m + 1] == ';' ? ";;" : ";");
        else
            my_message = (my_inpt[m - 1] == ';' ? ";;" : ";");
    }
    if (my_inpt[m] == '|')
        my_message = (my_inpt[m + 1] == '|' ? "||" : "|");
    if (my_inpt[m] == '&')
        my_message = (my_inpt[m + 1] == '&' ? "&&" : "&");
    my_massage2 = ": Syntax error: \"";
    my_message3 = "\" unexpected\n";
    full_counter = aux_itoa(ssh_list->counter);
    l = _strlen(ssh_list->av[0]) + _strlen(full_counter);
    l += _strlen(my_message) + _strlen(my_massage2) + _strlen(my_message3) + 2;
    error = malloc(sizeof(char) * (l + 1));
    if (error == 0)
    {
        free(full_counter);
        return;
    }
    _strcpy(error, ssh_list->av[0]);
    _strcat(error, ": ");
    _strcat(error, full_counter);
    _strcat(error, my_massage2);
    _strcat(error, my_message);
    _strcat(error, my_message3);
    _strcat(error, "\0");
    write(STDERR_FILENO, error, l);
    free(error);
    free(full_counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @ssh_list: lists structure
 * @my_inpt: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(lists_shell *ssh_list, char *my_inpt)
{

    int m = 0;

    int beginning = 0;

    int my_file_char = 0;

    my_file_char = first_char(my_inpt, &beginning);
    if (my_file_char == -1)
    {
        print_syntax_error(ssh_list, my_inpt, beginning, 0);
        return (1);
    }
    m = error_sep_op(my_inpt + beginning, 0, *(my_inpt + beginning));
    if (m != 0)
    {
        print_syntax_error(ssh_list, my_inpt, beginning + m, 1);
        return (1);
    }
    return (0);
}
