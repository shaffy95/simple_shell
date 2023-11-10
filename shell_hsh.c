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
		initialize_info(info);
		if (shell_is_active(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_result = get_input(info);
		if (read_result != -1)
		{
			configure_info(info, av);
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_command(info);
		}
		else if (shell_is_active(info))
			_putchar('\n');
		release_info(info, 0);
	}
	create_or_append_history(info);
	release_info(info, 1);
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
		{"setenv", set_env},
		{"unsetenv", un_setenv},
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
	int index, kite;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (index = 0, kite = 0; info->arg[index]; index++)
		if (!char_is_delim(info->arg[index], " \t\n"))
			kite++;
	if (!kite)
		return;

	path = find_executable_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((shell_is_active(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command_executable(info, info->argv[0]))
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			release_info(info, 1);
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
