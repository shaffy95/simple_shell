#include "shell.h"

/**
 * display_history - Displays the history list, one command per line, preceded
 *                  with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	print_command_history(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias to a string.
 * @info: Parameter struct
 * @alias_string: The string representing the alias.
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias_string)
{
	char *equal_sign_position, original_character;
	int result;

	equal_sign_position = _strchr(alias_string, '=');
	if (!equal_sign_position)
		return (1);

	original_character = *equal_sign_position;
	*equal_sign_position = 0;

	result = delete_alias(&(info->alias),
			find_alias(info->alias, alias_string, -1));

	*equal_sign_position = original_character;

	return (result);
}

/**
 * set_alias - Sets an alias to a string.
 * @info: Parameter struct
 * @alias_string: The string representing the alias.
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_string)
{
	char *equal_sign_position;

	equal_sign_position = _strchr(alias_string, '=');
	if (!equal_sign_position)
		return (1);

	if (!*++equal_sign_position)
		return (unset_alias(info, alias_string));

	unset_alias(info, alias_string);
	return (add_alias_end(&(info->alias), alias_string, 0) == NULL);
}

/**
 * print_alias_string - Prints an alias string.
 * @alias_node: The alias node to print.
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_t *alias_node)
{
	char *equal_sign_position = NULL, *alias = NULL;

	if (alias_node)
	{
		equal_sign_position = _strchr(alias_node->str, '=');
		for (alias = alias_node->str; alias <= equal_sign_position; alias++)
			_putchar(*alias);
		_putchar('\'');
		shell_puts(equal_sign_position + 1);
		shell_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_command - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int alias_command(info_t *info)
{
	int index = 0;
	char *equal_sign_position = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias_string(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		equal_sign_position = _strchr(info->argv[index], '=');
		if (equal_sign_position)
			set_alias(info, info->argv[index]);
		else
			print_alias_string(find_alias(info->alias, info->argv[index], '='));
	}

	return (0);
}
