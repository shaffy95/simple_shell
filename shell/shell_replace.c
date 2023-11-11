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
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[current] == '&' && buf[current + 1] == '&')
	{
		buf[current] = 0;
		current++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[current] == ';') /* found end of this command */
	{
		buf[current] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
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
 * @position: address of the current position in buf
 * @index: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *position,
		size_t index, size_t len)
{
	size_t current = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[index] = 0;
			current = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[index] = 0;
			current = len;
		}
	}

	*position = current;
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
		node = find_pnode(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		position = _strchr(node->str, '=');
		if (!position)
			return (0);
		position = _strdup(position + 1);
		if (!position)
			return (0);
		info->argv[0] = position;
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

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			replace_string(&(info->argv[index]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			replace_string(&(info->argv[index]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_pnode(info->env, &info->argv[index][1], '=');
		if (node)
		{
			replace_string(&(info->argv[index]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[index], _strdup(""));

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
