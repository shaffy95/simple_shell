#include "shell.h"

/**
 * free_and_null_pointer - Frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if the pointer was freed, otherwise 0.
 */
int free_and_null_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
