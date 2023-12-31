#include "shell.h"

/**
 * ufree - free memory given for a pointer and makes address NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if the memory was freed successfully, otherwise 0
 */
int ufree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
