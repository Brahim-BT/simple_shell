#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @hd: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *add_rvar_node(r_var **hd, int lvar, char *val, int lval)
{
	r_var *my_new, *my_temp;

	my_new = malloc(sizeof(r_var));
	if (my_new == NULL)
		return (NULL);

	my_new->len_var = lvar;
	my_new->val = val;
	my_new->len_val = lval;

	my_new->next = NULL;
	my_temp = *hd;

	if (my_temp == NULL)
	{
		*hd = my_new;
	}
	else
	{
		while (my_temp->next != NULL)
			my_temp = my_temp->next;
		my_temp->next = my_new;
	}

	return (*hd);
}

/**
 * free_rvar_list - frees a r_var list
 * @hd: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(r_var **hd)
{
	r_var *my_temp;
	r_var *my_currently;

	if (hd != NULL)
	{
		my_currently = *hd;
		while ((my_temp = my_currently) != NULL)
		{
			my_currently = my_currently->next;
			free(my_temp);
		}
		*hd = NULL;
	}
}
