#include "shell.h"

/**
 *_eputs - prints an input string to standard error.
 * @string: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *string)
{
    int index = 0;

    if (!string)
        return;
    while (string[index] != '\0')
    {
        _eputchar(string[index]);
        index++;
    }
}

/**
 * _eputchar - writes the character to standard error.
 * @character: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char character)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(2, buffer, index);
        index = 0;
    }
    if (character != BUF_FLUSH)
        buffer[index++] = character;
    return 1;
}

/**
 * _putfd - writes the character to the given file descriptor.
 * @character: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char character, int fd)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, index);
        index = 0;
    }
    if (character != BUF_FLUSH)
        buffer[index++] = character;
    return 1;
}

/**
 *_putsfd - prints an input string to the given file descriptor.
 * @string: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _putsfd(char *string, int fd)
{
    int count = 0;

    if (!string)
        return 0;
    while (*string)
    {
        count += _putfd(*string++, fd);
    }
    return count;
}
