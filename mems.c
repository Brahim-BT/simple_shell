#include "main.h"

/**
 * _memcpy - copies information between void pointers.
 * @newpntr: destination pointer.
 * @pntr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newpntr, const void *pntr, unsigned int size)
{
	char *char_pntr = (char *)pntr;
	char *char_newpntr = (char *)newpntr;
	unsigned int i;
	for (i = 0; i < size; i++)
		char_newpntr[i] = char_pntr[i];
}


/**
 * _realloc - reallocates a memory block.
 * @pntr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *pntr, unsigned int old_size, unsigned int new_size)
{
	void *newpntr;
	if (pntr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(pntr);
		return (NULL);
	}
	if (new_size == old_size)
		return (pntr);
	newpntr = malloc(new_size);
	if (newpntr == NULL)
		return (NULL);
	if (new_size < old_size)
		_memcpy(newpntr, pntr, new_size);
	else
		_memcpy(newpntr, pntr, old_size);
	free(pntr);
	return (newpntr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @pntr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

char **_reallocdp(char **pntr, unsigned int old_size, unsigned int new_size)
{
	char **newpntr;
	unsigned int i;

	if (pntr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (pntr);

	newpntr = malloc(sizeof(char *) * new_size);
	if (newpntr == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		newpntr[i] = pntr[i];
	free(pntr);

	return (newpntr);
}

