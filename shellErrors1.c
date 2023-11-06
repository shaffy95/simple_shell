#include "shell.h"

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int my;

	for (my = 0; buf[my] != '\0'; my++)
		if (buf[my] == '#' && (!my || buf[my - 1] == ' '))
		{
			buf[my] = '\0';
			break;
		}
}

/**
 * erratoi - Converts a string to an integer.
 * @strToConvert: The string to be converted.
 * Return: The converted number or -1 on error.
 */
int erratoi(char *strToConvert)
{
	int my = 0;
	unsigned long int result = 0;

	if (*strToConvert == '+')
		strToConvert++;  /* TODO: why does this make main return 255? */

	for (my = 0; strToConvert[my] != '\0'; my++)
	{
		if (strToConvert[my] >= '0' && strToConvert[my] <= '9')
		{
			result *= 10;
			result += (strToConvert[my] - '0');
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
	unsigned long nay = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		nay = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[nay % base];
		nay /= base;
	} while (nay != 0);

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
	int my, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = shell_eputchar;

	if (integer_to_print < 0)
	{
		_abs_ = -integer_to_print;
		__putchar('-');
		count++;
	}
	else
		_abs_ = integer_to_print;

	current = _abs_;
	for (my = 1000000000; my > 1; my /= 10)
	{
		if (_abs_ / my)
		{
			__putchar('0' + current / my);
			count++;
		}
		current %= my;
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
	shell_eputs(info->fname);
	shell_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	shell_eputs(": ");
	shell_eputs(info->argv[0]);
	shell_eputs(": ");
	shell_eputs(error_string);
}
