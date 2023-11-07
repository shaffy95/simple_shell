#include "shell.h"

/**
 * initialize_info - Initializes the info_t structure.
 * @information: Pointer to the info_t structure.
 */
void initialize_info(info_t *information)
{
	information->arguments = NULL;
	information->argument_count = 0;
	information->command_name = NULL;
}

/**
 * configure_info - Configures the info_t structure.
 * @information: Pointer to the info_t structure.
 * @arg_vector: Argument vector.
 */
void configure_info(info_t *information, char **arg_vector)
{
	int index = 0;

	information->command_name = arg_vector[0];
	if (information->arguments)
	{
		information->argument_vector = strtow(information->arguments, " \t");
		if (!information->argument_vector)
		{
			information->argument_vector = malloc(sizeof(char *) * 2);
			if (information->argument_vector)
			{
				information->argument_vector[0] = _strdup(information->arguments);
				information->argument_vector[1] = NULL;
			}
		}
		for (index = 0; information->argument_vector &&
				information->argument_vector[index]; index++)
			;
		information->argument_count = index;

		replace_aliases(information);
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
	ffree(information->argument_vector);
	information->argument_vector = NULL;
	information->path = NULL;
	if (free_all)
	{
		if (!information->command_buffer)
			free(information->argument);
		if (information->env)
			free_linked_list(&(information->env));
		if (information->history)
			free_linked_list(&(information->history));
		if (information->alias)
			free_linked_list(&(information->alias));
		ffree(information->environ);
		information->environ = NULL;
		bfree((void **)information->command_buffer);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
