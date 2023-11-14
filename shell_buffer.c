#include "shell.h"

/**
 * input_buf - Buffers chained commands from input.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @length: Address of length variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t buf_length = 0;

	if (!*length)
		/* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &buf_length, stdin);
#else
		bytes_read = _getline(info, buf, &buf_length);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				/* Remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			add_history_entry(info, *buf, info->histcount++);
			/* if (_strchr(*buffer, ';')) Is this a command chain? */
			{
				*length = bytes_read;
				info->cmd_buf = buf;
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
	static char *chain_buf;
	static size_t iterator, current_position, buf_length;
	ssize_t bytes_read = 0;
	char **buf_ptr = &(info->arg), *position;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &chain_buf, &buf_length);
	if (bytes_read == -1)
		return (-1);
	if (buf_length)
	{
		current_position = iterator;
		position = chain_buf + iterator;

		check_chain(info, chain_buf, &current_position, iterator,
				buf_length);
		while (current_position < buf_length)
		{
			if (chain_delimiter(info, chain_buf, &current_position))
				break;
			current_position++;
		}

		iterator = current_position + 1;
		if (iterator >= buf_length)
		{
			iterator = buf_length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_ptr = position;
		return (_strlen(position));
	}

	*buf_ptr = chain_buf;
	return (bytes_read);
}

/**
 * read_buf - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @length: Size.
 *
 * Return: Bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *length)
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
 * @buf_len: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Size.
 */
int _getline(info_t *info, char **ptr, size_t *buf_len)
{
	static char buf[READ_BUF_SIZE];
	static size_t iterator, length;
	size_t kite;
	ssize_t read_bytes = 0, seem = 0;
	char *post = NULL, *new_post = NULL, *court;

	post = *ptr;
	if (post && buf_len)
		seem = *buf_len;
	if (iterator == length)
		iterator = length = 0;

	read_bytes = read_buf(info, buf, &length);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
		return (-1);

	court = _strchr(buf + iterator, '\n');
	kite = court ? 1 + (unsigned int)(court - buf) : length;
	new_post = _realloc(post, seem, seem ? seem + kite : kite + 1);
	if (!new_post) /* MALLOC FAILURE! */
		return (post ? free(post), -1 : -1);

	if (seem)
		_strncat(new_post, buf + iterator, kite - iterator);
	else
		_strncpy(new_post, buf + iterator, kite - iterator + 1);

	seem += kite - iterator;
	iterator = kite;
	post = new_post;

	if (buf_len)
		*buf_len = seem;
	*ptr = post;
	return (seem);
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
