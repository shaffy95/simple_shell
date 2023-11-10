#include "shell.h"

/**
 * initialize_info - Initializes the info_t structure.
 * @information: Pointer to the info_t structure.
 */
void initialize_info(info_t *information)
{
	information->arg = NULL;
	information->argc = 0;
	information->argv = NULL;
	information->path = NULL;
}

/**
 * configure_info - Configures the info_t structure.
 * @information: Pointer to the info_t structure.
 * @arg_vector: Argument vector.
 */
void configure_info(info_t *information, char **arg_vector)
{
	int index = 0;

	information->fname = arg_vector[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (index = 0; information->argv && information->argv[index];
				index++)
			;
		information->argc = index;

		replace_alias(information);
		replace_variables(information);
	}
}

/**
 * release_info - Frees the info_t structure fields.
 * @information: Pointer to the info_t structure.
 * @free_all: true if freeing all fields.
 */
void release_info(info_t *information, int free_all)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (free_all)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_linked_list(&(information->env));
		if (information->history)
			free_linked_list(&(information->history));
		if (information->alias)
			free_linked_list(&(information->alias));
		ffree(information->environ);
		information->environ = NULL;
		free_and_null_pointer((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}
