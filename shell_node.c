#include "shell.h"

/**
 * insert_snode - Inserts a node at the beginning of the linked list
 * @list_hptr: Address of the pointer to the list's head
 * @str: Data to be stored in the node
 * @num: Index used for history
 *
 * Return: Size of the updated list
 */
list_t *insert_snode(list_t **list_hptr, const char *str, int num)
{
	list_t *new_node;

	if (!list_hptr)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *list_hptr;
	*list_hptr = new_node;
	return (new_node);
}

/**
 * insert_enode - Inserts a node at the end of the linked list
 * @list_hptr: Address of the pointer to the list's head
 * @str: Data to be stored in the node
 * @num: Index used for history
 *
 * Return: Size of the updated list
 */
list_t *insert_enode(list_t **list_hptr, const char *str, int num)
{
	list_t *new_node, *current_node;

	if (!list_hptr)
		return (NULL);

	current_node = *list_hptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*list_hptr = new_node;
	return (new_node);
}

/**
 * print_dlist - Prints only the data element of a list_t linked list
 * @first_node: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_dlist(const list_t *first_node)
{
	size_t size = 0;

	while (first_node)
	{
		_puts(first_node->str ? first_node->str : "(nil)");
		_puts("\n");
		first_node = first_node->next;
		size++;
	}
	return (size);
}

/**
 * remove_si_node - Removes a node at a given index
 * @list_hptr: Address of the pointer to the first node
 * @target_index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_si_node(list_t **list_hptr, unsigned int target_index)
{
	list_t *current_node, *previous_node;
	unsigned int index = 0;

	if (!list_hptr || !*list_hptr)
		return (0);

	if (!target_index)
	{
		current_node = *list_hptr;
		*list_hptr = (*list_hptr)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *list_hptr;
	while (current_node)
	{
		if (index == target_index)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		index++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * free_linked_list - Frees all nodes of a linked list
 * @head_ptr: Address of the pointer to the head node
 *
 * Return: void
 */
void free_linked_list(list_t **head_ptr)
{
	list_t *current_node, *next_node, *head_node;

	if (!head_ptr || !*head_ptr)
		return;
	head_node = *head_ptr;
	current_node = head_node;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*head_ptr = NULL;
}
