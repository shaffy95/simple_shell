#include "shell.h"

/**
 * free_and_null_pointer - Frees a pointer and sets it to NULL
 * @pointer: address of the pointer to free
 *
 * Return: 1 if the pointer was freed, otherwise 0.
 */
int free_and_null_pointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
