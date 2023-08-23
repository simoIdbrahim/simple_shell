#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: byte to fill.
 * @n: number of bytes.
 *
 * Return: pointer to the memory area.
 */

char *my_memset(char *s, char b, unsigned int n)
{
	unsigned int ind;

	for (ind = 0; ind < n; ind++)
		s[ind] = b;
	return (s);
}

/**
 * ffree  - Frees an array of strings.
 * @pp: The array of strings.
 */

void ffree(char **pp)
{
	char **temp = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(temp);
}

/**
 * _realloc - func block of memory.
 * @ptr: the arg Pointer to the previous allocated block.
 * @old_size: the arg Byte size of the previous block.
 * @new_size: the arg Byte size of the new block.
 *
 * Return: A pointer to the reallocated block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
