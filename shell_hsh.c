#include "shell.h"

/**
 * hsh - Main function for the shell
 * @info: A struct containing information and return values
 * @av: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (shell_is_active(info))
			shell_puts("$ ");
		shell_eputchar(BUF_FLUSH);
		read_result = get_input(info);
		if (read_result != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_command(info);
		}
		else if (shell_is_active(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!shell_is_active(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - Finds a built-in command
 * @info: The parameter & return info struct
 *
 * Return: -1 if built-in not found,
 *         0 if built-in executed successfully,
 *         1 if built-in found but not successful,
 *         -2 if built-in signals exit()
 */
int find_builtin(info_t *info)
{
	int index, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", exitShell},
		{"env", print_environment},
		{"help", showHelp},
		{"history", display_history},
		{"setenv", setenv},
		{"unsetenv", unsetenv},
		{"cd", changeCurrentDirectory},
		{"alias", alias_command},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[index].func(info);
			break;
		}
	return (built_in_result);
}

/**
 * find_command - Finds a command in PATH
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int index, g;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (index = 0, g = 0; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			g++;
	if (!g)
		return;

	path = find_path(info, getenv(info, "PATH="),
			info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive(info) || getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0])
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - Forks an exec thread to run a command
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getenv(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
