#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @hd: head of the linked list.
 * @my_sepr: separator found (; | &).
 * Return: address of the head.
 */
sep_list *add_sep_node_end(sep_list **hd, char my_sepr)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = my_sepr;
	new->next = NULL;
	temp = *hd;

	if (temp == NULL)
	{
		*hd = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*hd);
}

/**
 * free_sep_list - frees a sep_list
 * @hd: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **hd)
{
	sep_list *temp;
	sep_list *curr;

	if (hd != NULL)
	{
		curr = *hd;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*hd = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @hd: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **hd, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *hd;

	if (temp == NULL)
	{
		*hd = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*hd);
}

/**
 * free_line_list - frees a line_list
 * @hd: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **hd)
{
	line_list *temp;
	line_list *curr;

	if (hd != NULL)
	{
		curr = *hd;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*hd = NULL;
	}
}
