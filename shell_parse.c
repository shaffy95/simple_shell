#include "shell.h"

/**
 * is_command_executable - Determines if a file is an executable command
 * @info: Information struct
 * @file_path: Path to the file
 *
 * Return: 1 if it's an executable command, 0 otherwise
 */
int is_command_executable(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - Duplicates characters in a string
 * within a specified range
 * @path_string: The PATH string
 * @start_index: Starting index
 * @stop_index: Stopping index
 *
 * Return: Pointer to a new buffer containing duplicated characters
 */
char *duplicate_characters(char *path_string, int start_index, int stop_index)
{
	static char buffer[1024];
	int index = 0, g = 0;

	for (g = 0, index = start_index; index < stop_index; index++)
		if (path_string[index] != ':')
			buffer[g++] = path_string[index];
	buffer[g] = 0;
	return (buffer);
}

/**
 * find_executable_path - Finds the full path of a command in the PATH string
 * @info: Information struct
 * @path_string: The PATH string
 * @command: The command to find
 *
 * Return: The full path of the command if found, or NULL
 */
char *find_executable_path(info_t *info, char *path_string, char *command)
{
	int index = 0, current_position = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command_executable(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[index] || path_string[index] == ':')
		{
			path = duplicate_characters(path_string, current_position, index);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command_executable(info, path))
				return (path);
			if (!path_string[index])
				break;
			current_position = index;
		}
		index++;
	}
	return (NULL);
}
