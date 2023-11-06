#include "shell.h"

/**
 * list_length - Determines the length of the linked list
 * @first_node: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t list_length(const list_t *first_node)
{
	size_t count = 0;

	while (first_node)
	{
		first_node = first_node->next;
		count++;
	}
	return (count);
}

/**
 * list_to_array - Converts the list->str into an array of strings
 * @node: Pointer to the first node
 *
 * Return: Array of strings
 */
char **list_to_array(list_t *node)
{
	list_t *current_node = node;
	size_t array_size = list_length(node);
	size_t index;
	char **strings;
	char *string;

	if (!node || !array_size)
		return (NULL);
	strings = malloc(sizeof(char *) * (array_size + 1));
	if (!strings)
		return (NULL);
	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		string = malloc(_strlen(current_node->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < index; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, current_node->str);
		strings[index] = string;
	}
	strings[index] = NULL;
	return (strings);
}

/**
 * print_linked_list - Prints all elements of a list_t linked list
 * @first_node: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_linked_list(const list_t *first_node)
{
	size_t size = 0;

	while (first_node)
	{
		shell_puts(convert_number(first_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		shell_puts(first_node->str ? first_node->str : "(nil)");
		shell_puts("\n");
		first_node = first_node->next;
		size++;
	}
	return (size);
}

/**
 * find_pnode - Returns the node whose string starts with a prefix
 * @node: Pointer to the list head
 * @prefix: String to match
 * @next_char: The next character after the prefix to match
 *
 * Return: The matching node or NULL
 */
list_t *find_pnode(list_t *node, char *prefix, char next_char)
{
	char *m = NULL;

	while (node)
	{
		m = starts_with(node->str, prefix);
		if (m && ((next_char == -1) || (*m == next_char)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_inode - Gets the index of a node
 * @head_node: Pointer to the list head
 * @target_node: Pointer to the target node
 *
 * Return: Index of the node or -1
 */
ssize_t get_inode(list_t *head_node, list_t *target_node)
{
	size_t i = 0;

	while (head_node)
	{
		if (head_node == target_node)
			return (i);
		head_node = head_node->next;
		i++;
	}
	return (-1);
}
