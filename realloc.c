#include "shell.h"

/**
 * _memset - fills memory with constant byte
 * @s: pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the number of bytes to be filled
 *
 * Return: a pointer to the memory area @s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int as;

	for (as = 0; as < n; as++)
		s[as] = b;

	return (s);
}

/**
 * efree - the free array of strings
 * @bb: array of strings to free
 */
void efree(char **bb)
{
	char **b = bb;

	if (!bb)
		return;

	while (*bb)
		free(*bb++);

	free(b);
}

/**
 * _realloc - reallocates block of memory
 * @ptr: pointer to the previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *b;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	b = malloc(new_size);

	if (!t)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		b[old_size] = ((char *)ptr)[old_size];

	free(ptr);

	return (b);
}
