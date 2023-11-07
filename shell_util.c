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
	print_linked_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias.
 * @info: A pointer to the info_t structure.
 * @alias_string: The alias string to be removed.
 *
 * This function removes an alias from the info structure.
 * Return: 0 on success, 1 on failure.
 */
int unset_alias(info_t *info, char *alias_string)
{
	char *equal_sign_position;
	char original_character;
	int result;

	equal_sign_position = copyLimitedString(alias_string, "=", 1024);
	if (!equal_sign_position)
		return (1);

	original_character = *equal_sign_position;
	*equal_sign_position = 0;

	result = remove_si_node(&(info->alias),
			get_inode(info->alias,
				find_pnode(info->alias, alias_string, -1)));

	*equal_sign_position = original_character;

	return (result);
}

/**
 * set_alias - Sets an alias in the info structure.
 * @info: A pointer to the info_t structure.
 * @alias_string: The alias string to be set.
 *
 * This function sets an alias in the info structure.
 * Return: 0 on success, 1 on failure.
 */
int set_alias(info_t *info, char *alias_string)
{
	char *equal_sign_position;

	equal_sign_position = copyLimitedString(alias_string, "=", 1024);
	if (!equal_sign_position)
		return (1);

	if (!*++equal_sign_position)
		return unset_alias(info, alias_string);

	unset_alias(info, alias_string);
	return (insert_enode(&(info->alias), alias_string, 0) == NULL);
}


/**
 * print_alias - Prints an alias string.
 * @alias_node: The alias node to print.
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *equal_sign_position = NULL, *alias = NULL;

	if (alias_node)
	{
		equal_sign_position = copyLimitedString(alias_node->alias_string, "=", 1024);
		for (alias = alias_node->alias_string; alias <= equal_sign_position; alias++)
			_putchar(*alias);
		_putchar('\'');
		shell_puts(equal_sign_position + 1);
		shell_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_command - Handles alias command (Mimics).
 * @info: A pointer to the info_t structure.
 *
 * This function manages the alias command, setting and printing aliases.
 * Return: 0 on success.
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
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (index = 1; info->argv[index]; index++)
	{
		equal_sign_position = copyLimitedString(info->argv[index], "=", 1024);
		if (equal_sign_position)
			set_alias(info, info->argv[index]);
		else
			print_alias(find_pnode(info->alias, info->argv[index], '='));
	}

	return (0);
}
