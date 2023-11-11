#include "shell.h"

/**
 * input_buffer - Buffers chained commands from input.
 * @info: Parameter struct.
 * @buffer: Address of the buffer.
 * @length: Address of length variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t buffer_length = 0;

	if (!*length)
		/* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &buffer_length, stdin);
#else
		bytes_read = _getline(info, buffer, &buffer_length);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				/* Remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			add_history_entry(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) Is this a command chain? */
			{
				*length = bytes_read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - Gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *chain_buffer;
	static size_t chain_iterator, current_position, buffer_length;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *position;

	_putchar(BUF_FLUSH);
	bytes_read = input_buffer(info, &chain_buffer, &buffer_length);
	if (bytes_read == -1)
		return (-1);
	if (buffer_length)
	{
		current_position = chain_iterator;
		position = chain_buffer + chain_iterator;

		check_chain(info, chain_buffer, &current_position, chain_iterator,
				buffer_length);
		while (current_position < buffer_length)
		{
			if (chain_delimiter(info, chain_buffer, &current_position))
				break;
			current_position++;
		}

		chain_iterator = current_position + 1;
		if (chain_iterator >= buffer_length)
		{
			chain_iterator = buffer_length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_ptr = position;
		return (_strlen(position));
	}

	*buffer_ptr = chain_buffer;
	return (bytes_read);
}

/**
 * read_buffer - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @length: Size.
 *
 * Return: Bytes read.
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *length)
{
	ssize_t bytes_read = 0;

	if (*length)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*length = bytes_read;
	return (bytes_read);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of a pointer to a buffer, preallocated or NULL.
 * @buffer_length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Size.
 */
int _getline(info_t *info, char **ptr, size_t *buffer_length)
{
	static char buf[READ_BUF_SIZE];
	static size_t buffer_iterator, buffer_len;
	size_t k;
	ssize_t bytes_read = 0, size = 0;
	char *position = NULL, *new_position = NULL, *c;

	position = *ptr;
	if (position && buffer_length)
		size = *buffer_length;
	if (buffer_iterator == buffer_len)
		buffer_iterator = buffer_len = 0;

	bytes_read = read_buffer(info, buf, &buffer_len);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_len == 0))
		return (-1);

	c = _strchr(buf + buffer_iterator, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : buffer_len;
	new_position = _realloc(position, size, size ? size + k : k + 1);
	if (!new_position) /* MALLOC FAILURE! */
		return (position ? free(position), -1 : -1);

	if (size)
		_strncat(new_position, buf + buffer_iterator, k - buffer_iterator);
	else
		_strncpy(new_position, buf + buffer_iterator, k - buffer_iterator + 1);

	size += k - buffer_iterator;
	buffer_iterator = k;
	position = new_position;

	if (buffer_length)
		*buffer_length = size;
	*ptr = position;
	return (size);
}

/**
 * sigintHandler - Blocks Ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
