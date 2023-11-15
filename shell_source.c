#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of the string
 */
int _strlen(char *string)
{
	int length = 0;

	if (!string)
		return (0);

	while (*string++)
		length++;
	return (length);
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @hot1: the first string
 * @hot2: the second string
 *
 * Return: negative if hot1 < hot2, positive if hot1 > hot2,
 * zero if hot1 == hot2
 */
int _strcmp(char *hot1, char *hot2)
{
	while (*hot1 && *hot2)
	{
		if (*hot1 != *hot2)
			return (*hot1 - *hot2);
		hot1++;
		hot2++;
	}
	if (*hot1 == *hot2)
		return (0);
	else
		return (*hot1 < *hot2 ? -1 : 1);
}

/**
 * starts_with - checks if a string starts with a prefix
 * @haystack: the string to search
 * @needle: the prefix to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_strcat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (result);
}
