#include "shell.h"

/**
 * allocate_array - Allocates memory for the word_array
 * @count: The number of words
 * @array: A pointer to the word_array
 * @string: The input string
 * @dex: The current character index
 * @delim: The delimiters used for splitting
 * Return: 1 on success, 0 on failure
 */
int allocate_array(int count, char **array, char *string, int dex, char *delim)
{
	int word_index = 0, char_copy = 0;

	while (word_index < count)
	{
		while (is_delimiter(string[dex], delim))
			dex++;

		char_copy = 0;

		while (!is_delimiter(string[dex + char_copy], delim) &&
				string[dex + char_copy])
			char_copy++;

		array[word_index] = malloc((char_copy + 1) * sizeof(char));

		if (!array[word_index])
		{
			while (word_index > 0)
				free(array[--word_index]);
			free(array);
			return (0);
		}

		for (int index = 0; index < char_copy; index++)
			array[word_index][index] = string[dex++];
		array[word_index][char_copy] = 0;
		word_index++;
	}
	array[word_index] = NULL;
	return (1);
}

/**
 * split_string - splits a string into words using specified delimiters
 * @input_string: the input string to be split
 * @delim: the delimiters used for splitting
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *input_string, char *delim)
{
	int index = 0, count = 0;
	char **word_array;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);

	if (!delim)
		delim = " ";

	while (input_string[index] != '\0')
	{
		if (!is_delimiter(input_string[index], delim) &&
				(is_delimiter(input_string[index + 1], delim)
				 || !input_string[_index + 1]))
		{
			count++;
		}
		index++;
	}

	if (count == 0)
		return (NULL);

	word_array = malloc((1 + count) * sizeof(char *);
			if (!word_array)
			return (NULL);

			if (!allocate_array(count, word_array, input_string, 0, delim))
			return (NULL);

			return (word_array);
}
