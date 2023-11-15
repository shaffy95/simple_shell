#include "shell.h"

/**
 * get_environ - Returns a copy of the string
 * array representing the environment.
 * @information: A structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *information)
{
	if (!information->environ ||
			information->env_changed)
	{
		information->environ =
			list_to_array(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 * @information: A structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * Return: 1 on successful deletion, 0 otherwise
 * @variable: The property of the environment variable to remove
 */
int _unsetenv(info_t *information, char *variable)
{
	list_t *node = information->env;
	size_t index = 0;
	char *pointer;

	if (!node || !variable)
		return (0);

	while (node)
	{
		pointer = starts_with(node->str, variable);
		if (pointer && *pointer == '=')
		{
			information->env_changed = remove_si_node
				(&(information->env), index);
			index = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (information->env_changed);
}

/**
 * _setenv - Initialize a new environment
 * variable or modify an existing one.
 * @information: A structure containing potential arguments.
 * Used to maintain a constant function prototype.
 * @variable: The property of the environment variable
 * @value: The value of the environment variable
 * Return: Always 0
 */
int _setenv(info_t *information, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *pointer;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = information->env;
	while (node)
	{
		pointer = starts_with(node->str, variable);
		if (pointer && *pointer == '=')
		{
			free(node->str);
			node->str = buffer;
			information->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	insert_enode(&(information->env), buffer, 0);
	free(buffer);
	information->env_changed = 1;
	return (0);
}
