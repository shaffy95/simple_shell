#include "shell.h"

/**
 * chain_delimiter - checks if the current character in the
 * buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the character buffer
 * @position: address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int chain_delimiter(info_t *info, char *buf, size_t *position)
{
	size_t current = *position;

	if (buf[current] == '|' && buf[current + 1] == '|')
	{
		buf[current] = 0;
		current++;
		info->command_buffer_type = CMD_OR;
	}
	else if (buf[current] == '&' && buf[current + 1] == '&')
	{
		buf[current] = 0;
		current++;
		info->command_buffer_type = CMD_AND;
	}
	else if (buf[current] == ';') /* Found the end of this command */
	{
		buf[current] = 0; /* Replace semicolon with null */
		info->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);

	*position = current;
	return (1);
}

/**
 * check_chain - checks whether to continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @pst: address of the current position in buf
 * @stat: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *pst, size_t stat, size_t len)
{
	size_t current = *pst;

	if (info->command_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buf[stat] = 0;
			current = len;
		}
	}
	if (info->command_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[stat] = 0;
			current = len;
		}
	}

	*pst = current;
}

/**
 * replace_alias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int index;
	list_t *node;
	char *position;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(info->alias, info->arguments[0], '=');
		if (!node)
			return (0);
		free(info->arguments[0]);
		position = _strchr(node->str, '=');
		if (!position)
			return (0);
		position = _strdup(position + 1);
		if (!position)
			return (0);
		info->arguments[0] = position;
	}
	return (1);
}

/**
 * replace_variables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->arguments[index]; index++)
	{
		if (info->arguments[index][0] != '$' || !info->arguments[index][1])
			continue;

		if (!_strcmp(info->arguments[index], "$?"))
		{
			replace_string(&(info->arguments[index]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->arguments[index], "$$"))
		{
			replace_string(&(info->arguments[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->environment, &info->arguments[index][1], '=');
		if (node)
		{
			replace_string(&(info->arguments[index]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->arguments[index], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces a string
 * @old_str: address of the old string
 * @new_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
