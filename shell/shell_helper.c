#include "shell.h"

/**
 * char_is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int char_is_delim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}


/**
 * char_is_alpha - checks for alphabetic character
 * @f: The character to input
 * Return: 1 if f is alphabetic, 0 otherwise
 */

int char_is_alpha(int f)
{
	if ((f >= 'a' && f <= 'z') || (f >= 'A' && f <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *string_to_integer - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int string_to_integer(char *str)
{
	int index, sign = 1, state = 0, result_integer;
	unsigned int result_value = 0;

	for (index = 0; str[index] != '\0' && state != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			state = 1;
			result_value *= 10;
			result_value += (str[index] - '0');
		}
		else if (state == 1)
			state = 2;
	}

	if (sign == -1)
		result_integer = -result_value;
	else
		result_integer = result_value;

	return (result_integer);
}

/**
 * shell_is_active - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int shell_is_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
