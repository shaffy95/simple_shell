nclude "shell.h"

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
    int i = 0;

    information->command_name = arg_vector[0];
    if (information->arguments)
    {
        information->argument_vector = string_split(information->arguments, " \t");
        if (!information->argument_vector)
        {
            information->argument_vector = malloc(sizeof(char *) * 2);
            if (information->argument_vector)
            {
                information->argument_vector[0] = string_duplicate(information->arguments);
                information->argument_vector[1] = NULL;
            }
        }
        for (i = 0; information->argument_vector && information->argument_vector[i]; i++)
            ;
        information->argument_count = i;

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
    free_string_array(information->argument_vector);
    information->argument_vector = NULL;
    information->path = NULL;
    if (free_all)
    {
        if (!information->command_buffer)
            free(information->arguments);
        if (information->environment)
            free_list(&(information->environment));
        if (information->history)
            free_list(&(information->history));
        if (information->aliases)
            free_list(&(information->aliases));
        free_string_array(information->environment_variables);
        information->environment_variables = NULL;
        free_buffer((void **)information->command_buffer);
        if (information->read_fd > 2)
            close(information->read_fd);
        _putchar(BUFFER_FLUSH);
    }
}
