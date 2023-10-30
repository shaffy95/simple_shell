#include "shell.h"

/**
 * char_is_delim - Check if a character is present in a delimiter string.
 * @ch: The character to check.
 * @delim: The delimiter string to search.
 *
 * This function iterates through the delimiter string until it finds a match
 * with the provided character. If a match is found, it returns 1; otherwise, it
 * returns 0.
 *
 * @return: 1 if character is found in the delimiter string, 0 otherwise.
 */
int char_is_delim(char ch, const char *delim)
{
    while (*delim != '\0')
    {
        if (*delim == ch)
            return 1;
        delim++;
    }
    return 0;
}


/**
 * char_is_alpha - checks for alphabetic character
 * @f: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int char_is_alpha(int f)
{
        if ((f >= 'a' && f <= 'z') || (f >= 'A' && f <= 'Z'))
                return (1);
        else
                return (0);
}

/**
 * string_to_integer - Convert a string to an integer.
 * @str: The input string to be converted.
 *
 * This function attempts to convert the given string to an integer. It iterates
 * through the characters in the string, considering the sign (positive or
 * negative) and numeric characters ('0' to '9'). If successful, it returns the
 * converted integer; otherwise, it returns 0.
 *
 * @return: The converted integer value or 0 if the conversion fails.
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

    return result_integer;
}

/**
 * shell_is_active - returns true if shell is interactive mode
 * @input: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int shell_is_active(input_t *input)
{
        return (isatty(STDIN_FILENO) && input->readfd <= 2);
}
