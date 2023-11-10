#include "shell.h"

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int index, last = 0, lineCt = 0;
	ssize_t fd, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(fd, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(fd);
	for (index = 0; index < file_size; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			add_history_entry(info, buffer + last, lineCt++);
			last = index + 1;
		}
	if (last != index)
		add_history_entry(info, buffer + last, lineCt++);
	free(buffer);
	info->histcount = lineCt;
	while (info->histcount-- >= HIST_MAX)
		remove_si_node(&(info->history), 0);
	update_history_count(info);
	return (info->histcount);
}

/**
 * get_history_file - Retrieve the path to the history file
 * @information: The parameter struct containing relevant information
 *
 * Return: Allocated string containing the history file path
 */
char *get_history_file(info_t *information)
{
	char *history_directory, *history_path;

	history_path = _getenv(information, "HOME=");
	if (!history_path)
		return (NULL);
	history_directory = malloc(sizeof(char) * (_strlen(history_path)
				+ _strlen(HIST_FILE) + 2));
	if (!history_directory)
		return (NULL);
	history_directory[0] = 0;
	_strcpy(history_directory, history_path);
	_strcat(history_directory, "/");
	_strcat(history_directory, HIST_FILE);
	return (history_directory);
}

/**
 * create_or_append_history - Creates a file or appends to an existing file
 * @information: The parameter struct containing relevant information
 *
 * Return: 1 on success, else -1
 */
int create_or_append_history(info_t *information)
{
	ssize_t fd;
	char *file_name = get_history_file(information);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);

	if (fd == -1)
		return (-1);

	for (node = information->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}


/**
 * add_history_entry - Appends an entry to the history linked list
 * @info: Structure containing relevant information
 * @entry_text: The text to be added to the history
 * @entry_count: The count of history entries
 *
 * Return: Always 0
 */
int add_history_entry(info_t *info, char *entry_text, int entry_count)
{
	list_t *new_entry = NULL;

	if (info->history)
		new_entry = info->history;

	insert_enode(&new_entry, entry_text, entry_count);

	if (!info->history)
		info->history = new_entry;

	return (0);
}

/**
 * update_history_count - Recalculates the history count after modifications
 * @info: Structure containing historical data and related arguments
 *
 * Return: the updated history count
 */
int update_history_count(info_t *info)
{
	list_t *current_node = info->history;
	int history_count = 0;

	while (current_node)
	{
		current_node->num = history_count++;
		current_node = current_node->next;
	}

	info->histcount = history_count;
	return (history_count);
}
