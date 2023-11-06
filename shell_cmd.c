#include "shell.h"

/**
 * print_environment - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
	print_environment_list(info->env);
	return (0);
}

/**
 * get_environment_variable - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * @variable_name: Name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_environment_variable(info_t *info, const char *variable_name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, variable_name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initializes a new
 * environment variable or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on failure
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		shell_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (set_environment_variable(info, info->argv[1], info->argv[2]) == 0)
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		shell_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_environment_variable(info, info->argv[i]);

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
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
