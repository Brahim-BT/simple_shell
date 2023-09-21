#include "main.h"

/**
 * _memcpy - copies information between void pointers.
 * @my_newptr: destination pointer.
 * @my_ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *my_newptr, const void *my_ptr, unsigned int size)
{
	char *char_ptr = (char *)my_ptr;
	char *char_newptr = (char *)my_newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - reallocates a memory block.
 * @my_ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: my_ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *my_ptr, unsigned int old_size, unsigned int new_size)
{
	void *my_newptr;

	if (my_ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(my_ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (my_ptr);

	my_newptr = malloc(new_size);
	if (my_newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(my_newptr, my_ptr, new_size);
	else
		_memcpy(my_newptr, my_ptr, old_size);

	free(my_ptr);
	return (my_newptr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @my_ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **my_ptr, unsigned int old_size, unsigned int new_size)
{
	char **my_newptr;
	unsigned int i;

	if (my_ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (my_ptr);

	my_newptr = malloc(sizeof(char *) * new_size);
	if (my_newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		my_newptr[i] = my_ptr[i];

	free(my_ptr);

	return (my_newptr);
}
