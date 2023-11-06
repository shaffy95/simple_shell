#include "shell.h"

/**
 * get_environment - Returns a copy of the string
 * array representing the environment.
 * @information: A structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * Return: Always 0
 */
char **get_environment(info_t *information)
{
	if (!information->environment ||
			information->environment_changed)
	{
		information->environment =
			list_to_strings(information->environment_list);
		information->environment_changed = 0;
	}

	return (information->environment);
}

/**
 * unsetenv - Remove an environment variable.
 * @information: A structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * Return: 1 on successful deletion, 0 otherwise
 * @variable: The property of the environment variable to remove
 */
int unsetenv(info_t *information, char *variable)
{
	list_t *node = information->environment_list;
	size_t index = 0;
	char *ptr;

	if (!node || !variable)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, variable);
		if (ptr && *ptr == '=')
		{
			information->environment_changed =
				delete_node_at_index
				(&(information->environment_list), index);
			index = 0;
			node = information->environment_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return (information->environment_changed);
}

/**
 * setenv - Initialize a new environment
 * variable or modify an existing one.
 * @information: A structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * @variable: The property of the environment variable
 * @value: The value of the environment variable
 * Return: Always 0
 */
int setenv(info_t *information, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = information->environment_list;
	while (node)
	{
		ptr = starts_with(node->str, variable);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			information->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(information->environment_list), buffer, 0);
	free(buffer);
	information->environment_changed = 1;
	return (0);
}
