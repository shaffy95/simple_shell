#include "shell.h"

/**
 * copy_string - copies a string from source to destination
 * @destination: the destination buffer
 * @source: the source string
 *
 * Return: pointer to the destination buffer
 */
char *copy_string(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return destination;
}

/**
 * duplicate_string - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicate_string(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return NULL;
	while (*str++)
		length++;
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
		return NULL;
	for (length++; length--;)
		duplicate[length] = *--str;
	return duplicate;
}

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		print_character(str[index]);
		index++;
	}
}

/**
 * print_character - writes the character to standard output
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_character(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return 1;
}
