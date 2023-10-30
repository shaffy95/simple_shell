#include "shell.h"

/**
 * split_string - splits a string into words using specified delimiters
 * @input_string: the input string to be split
 * @delimiters: the delimiters used for splitting
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *input_string, char *delimiters)
{
	int char_index, word_index, char_count, char_copy;
	char **word_array;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);

	if (!delimiters)
		delimiters = " ";  /* Default delimiter is space */

	for (char_index = 0; input_string[char_index] != '\0'; char_index++)
	{
		if (!is_delimiter(input_string[char_index], delimiters) &&
		    (is_delimiter(input_string[char_index + 1], delimiters)
		     || !input_string[char_index + 1]))
		{
			char_count++;
		}
	}

	if (char_count == 0)
		return (NULL);

	word_array = malloc((1 + char_count) * sizeof(char *));
	if (!word_array)
		return (NULL);

	for (char_index = 0, word_index = 0; word_index < char_count; word_index++)
	{
		while (is_delimiter(input_string[char_index], delimiters))
			char_index++;

		char_copy = 0;

		while (!is_delimiter(input_string[char_index + char_copy],
		delimiters) && input_string[char_index + char_copy])
			char_copy++;

		word_array[word_index] = malloc((char_copy + 1) * sizeof(char));

		if (!word_array[word_index])
		{
			for (char_copy = 0; char_copy < word_index; char_copy++)
				free(word_array[char_copy]);
			free(word_array);
			return (NULL);
	}

		for (char_copy = 0; char_copy < char_copy; char_copy++)
			word_array[word_index][char_copy] = input_string[char_index++];
		word_array[word_index][char_copy] = 0;
	}
	word_array[word_index] = NULL;
	return word_array;
}
