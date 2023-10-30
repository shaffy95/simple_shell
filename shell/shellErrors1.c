#include "shell.h"

/**remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int m;

	for (m = 0; buf[m] != '\0'; m++)
		if (buf[m] == '#' && (!m || buf[m - 1] == ' '))
		{
			buf[m] = '\0';
			break;
		}
}

/**
 * erratoi - Converts a string to an integer.
 * @str_to_convert: The string to be converted.
 * Return: The converted number or -1 on error.
 */
int erratoi(char *strToConvert)
{
    int m = 0;
    unsigned long int result = 0;

    if (*strToConvert == '+')
        strToConvert++;  /* TODO: why does this make main return 255? */

    for (m = 0; strToConvert[m] != '\0'; m++)
    {
        if (strToConvert[m] >= '0' && strToConvert[m] <= '9')
        {
            result *= 10;
            result += (strToConvert[m] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }

    return (result);
}

/**
 * convert_number - Converts a number to a string.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * Return: The converted string.
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return (ptr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @integer_to_print: The input integer.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_d(int integer_to_print, int fd)
{
    int (*__putchar)(char) = _putchar;
    int m, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;

    if (integer_to_print < 0)
    {
        _abs_ = -integer_to_print;
        __putchar('-');
        count++;
    }
    else
        _abs_ = integer_to_print;

    current = _abs_;
    for (m = 1000000000; m > 1; m /= 10)
    {
        if (_abs_ / m)
        {
            __putchar('0' + current / m);
            count++;
        }
        current %= m;
    }

    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * print_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @error_string: The string containing the specified error type.
 */
void print_error(info_t *info, char *error_string)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(error_string);
}
