#include "shell.h"

/**
 * _strncpy - copies a string up to a certain limit
 * @destination: the destination string to be copied to
 * @source: the source string
 * @limit: the maximum number of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *destination, char *source, int limit)
{
	int sourceIndex, destIndex;
	char *result = destination;

	sourceIndex = 0;
	while (source[sourceIndex] != '\0' && sourceIndex < limit - 1)
	{
		destination[sourceIndex] = source[sourceIndex];
		sourceIndex++;
	}
	if (sourceIndex < limit)
	{
		destIndex = sourceIndex;
		while (destIndex < limit)
		{
			destination[destIndex] = '\0';
			destIndex++;
		}
	}
	return (result);
}

/**
 * concatenateLimitedStrings - concatenates two strings with a character limit
 * @first: the first string
 * @second: the second string
 * @limit: the maximum number of characters to be used
 * Return: the concatenated string
 */
char *concatenateLimitedStrings(char *first, char *second, int limit)
{
	int firstIndex, secondIndex;
	char *result = first;

	firstIndex = 0;
	secondIndex = 0;
	while (first[firstIndex] != '\0')
		firstIndex++;
	while (second[secondIndex] != '\0' && secondIndex < limit)
	{
		first[firstIndex] = second[secondIndex];
		firstIndex++;
		secondIndex++;
	}
	if (secondIndex < limit)
		first[firstIndex] = '\0';
	return (result);
}

/**
 **findCharacterInString - locates a character in a string
 *@stringToSearch: the string to be parsed
 *@characterToFind: the character to look for
 *Return: (stringToSearch) a pointer to the memory area of the string
 */
char *findCharacterInString(char *stringToSearch, char characterToFind)
{
	do {
		if (*stringToSearch == characterToFind)
			return (stringToSearch);
	} while (*stringToSearch++ != '\0');

	return (NULL);
}
