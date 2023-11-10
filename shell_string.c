#include "shell.h"

/**
 * _strcpy - copies a string from source to destination
 * @destination: the destination buffer
 * @source: the source string
 *
 * Return: pointer to the destination buffer
 */
char *_strcpy(char *destination, char *source)
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
	return (destination);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
		return (NULL);
	for (length++; length--;)
		duplicate[length] = *--str;
	return (duplicate);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - writes the character to standard output
 * @xee: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char xee)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (xee == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (xee != BUF_FLUSH)
		buffer[index++] = xee;
	return (1);
}
