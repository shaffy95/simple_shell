#include "shell.h"

/**
 * _memset - Fills memory with a constant byte
 * @dest: The pointer to the memory area to fill
 * @byte: The byte to fill *dest with
 * @count: The number of bytes to be filled
 *
 * Return: A pointer to the memory area dest
 */
char *_memset(char *dest, char byte, unsigned int count)
{
	unsigned int index;

	for (index = 0; index < count; index++)
		dest[index] = byte;
	return (dest);
}

/**
 * ffree - Frees an array of strings
 * @str_array: The array of strings to free
 */
void ffree(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * _realloc - Reallocates a block of memory
 * @old_ptr: Pointer to the previously malloc'ated block
 * @old_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 *
 * Return: Pointer to the reallocated block of memory
 */
void *_realloc(void *old_ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!old_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(old_ptr), NULL);
	if (new_size == old_size)
		return (old_ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)old_ptr)[old_size];
	free(old_ptr);
	return (new_ptr);
}
