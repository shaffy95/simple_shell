#include "shell.h"

/**
 * print_environment - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
	print_dlist(info->env);
	return (0);
}

/**
 * get_env - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * @variable_name: Name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_env(info_t *info, const char *variable_name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = string_starts_with(node->str, variable_name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Initializes a new
 * environment variable or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on failure
 */
int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]) == 0)
		return (0);
	return (1);
}

/**
 * un_setenv - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int un_setenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		insert_enode(&node, environ[index], 0);
	info->env = node;
	return (0);
}
