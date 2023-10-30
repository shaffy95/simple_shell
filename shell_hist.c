#include "shell.h"

/** read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
    int index, last_index = 0, line_count = 0;
    ssize_t file_descriptor, read_length, file_size = 0;
    struct stat file_stat;
    char *buffer = NULL, *history_file = get_history_file(info);

    if (!history_file)
        return (0);

    file_descriptor = open(history_file, O_RDONLY);
    free(history_file);
    if (file_descriptor == -1)
        return (0);

    if (!fstat(file_descriptor, &file_stat))
        file_size = file_stat.st_size;

    if (file_size < 2)
        return (0);

    buffer = malloc(sizeof(char) * (file_size + 1));
    if (!buffer)
        return (0);

    read_length = read(file_descriptor, buffer, file_size);
    buffer[file_size] = 0;

    if (read_length <= 0)
        return (free(buffer), 0);

    close(file_descriptor);

    for (index = 0; index < file_size; index++)
        if (buffer[index] == '\n')
        {
            buffer[index] = 0;
            build_history_list(info, buffer + last_index, line_count++);
            last_index = index + 1;
        }

    if (last_index != index)
        build_history_list(info, buffer + last_index, line_count++);

    free(buffer);
    info->histcount = line_count;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);
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

    history_directory = _getenv(information, "HOME=");
    if (!history_directory)
        return (NULL);

    size_t path_length = _strlen(history_directory) + _strlen(HIST_FILE) + 2;
    history_path = malloc(sizeof(char) * path_length);

    if (!history_path)
    {
        free(history_directory);
        return (NULL);
    }

    history_path[0] = 0;
    _strcpy(history_path, history_directory);
    _strcat(history_path, "/");
    _strcat(history_path, HIST_FILE);

    free(history_directory);
    return (history_path);
}

/**
 * create_or_append_history - Creates a file or appends to an existing file
 * @information: The parameter struct containing relevant information
 *
 * Return: 1 on success, else -1
 */
int create_or_append_history(info_t *information)
{
    ssize_t file_descriptor;
    char *file_name = get_history_file(information);
    list_t *node = NULL;

    if (!file_name)
        return (-1);

    file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);

    if (file_descriptor == -1)
        return (-1);

    for (node = information->history; node; node = node->next)
    {
        _putsfd(node->str, file_descriptor);
        _putfd('\n', file_descriptor);
    }

    _putfd(BUF_FLUSH, file_descriptor);
    close(file_descriptor);

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

    if (info->command_history)
        new_entry = info->command_history;

    add_node_end(&new_entry, entry_text, entry_count);

    if (!info->command_history)
        info->command_history = new_entry;

    return 0;
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
    return history_count;
}
