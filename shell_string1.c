#include "shell.h"

/**
 * strtow2 - Allocates memory for the word_array
 * @str: The input string
 * @delim: The delimiters used for splitting
 * Return: 1 on success, 0 on failure
 */
char **strtow2(char *str, char delim)
{
	int index, current, kite, maze, nums = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (index = 0; str[index] != '\0'; index++)
		if ((str[index] != delim && str[index + 1] == delim) ||
				(str[index] != delim && !str[index + 1]) || str[index + 1] == delim)
			nums++;
	if (nums == 0)
		return (NULL);
	string = malloc((1 + nums) * sizeof(char *));
	if (!string)
		return (NULL);
	for (index = 0, current = 0; current < nums; current++)
	{
		while (str[index] == delim && str[index] != delim)
			index++;
		kite = 0;
		while (str[index + kite] != delim && str[index + kite] &&
				str[index + kite] != delim)
			kite++;
		string[current] = malloc((kite + 1) * sizeof(char));
		if (!string[current])
		{
			for (kite = 0; kite < current; kite++)
				free(string[kite]);
			free(string);
			return (NULL);
		}
		for (maze = 0; maze < kite; maze++)
			string[current][maze] = str[index++];
		string[current][maze] = 0;
	}
	string[current] = NULL;
	return (string);
}

/**
 * strtow - splits a string into words using specified delimiters
 * @str: the input string to be split
 * @delim: the delimiters used for splitting
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *delim)
{
	int index, current, kite, maze, nums = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (index = 0; str[index] != '\0'; index++)
		if (!char_is_delim(str[index], delim) && (char_is_delim(str[index + 1],
						delim) || !str[index + 1]))
			nums++;

	if (nums == 0)
		return (NULL);
	string = malloc((1 + nums) * sizeof(char *));
	if (!string)
		return (NULL);
	for (index = 0, current = 0; current < nums; current++)
	{
		while (char_is_delim(str[index], delim))
			index++;
		kite = 0;
		while (!char_is_delim(str[index + kite], delim) && str[index + kite])
			kite++;
		string[current] = malloc((kite + 1) * sizeof(char));
		if (!string[current])
		{
			for (kite = 0; kite < current; kite++)
				free(string[kite]);
			free(string);
			return (NULL);
		}
		for (maze = 0; maze < kite; maze++)
			string[current][maze] = str[index++];
		string[current][maze] = 0;
	}
	string[current] = NULL;
	return (string);
}
