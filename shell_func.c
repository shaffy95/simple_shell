#include "shell.h"

/**
 * exitShell - Exits the shell.
 * @shellInfo: Structure containing potential arguments.
 *
 * This function handles the 'exit' command to exit the shell.
 * If an argument is provided, it sets the shell's exit status and exits.
 *
 * Return: Always returns 0.
 */
int exitShell(info_t *shellInfo)
{
	int exitStatus;

	if (shellInfo->argv[1])
	{
		exitStatus = erratoi(shellInfo->argv[1]);
		if (exitStatus == -1)
		{
			shellInfo->status = 2;
			print_error(shellInfo, "Illegal number: ");
			_eputs(shellInfo->argv[1]);
			_eputchar('\n');
			return (1);
		}
		shellInfo->err_num = erratoi(shellInfo->argv[1]);
		return (-2);
	}
	shellInfo->err_num = -1;
	return (-2);
}

/**
 * changeCurrentDirectory - Changes the current directory of the process.
 * @shellInfo: Structure containing potential arguments.
 *
 * This function handles the 'cd' command to change the current directory.
 *
 * Return: Always returns 0.
 */
int changeCurrentDirectory(info_t *shellInfo)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirRet;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: Handle getcwd failure message here\n");
	if (!shellInfo->argv[1])
	{
		newDir = _getenv(shellInfo, "HOME=");
		if (!newDir)
			chdirRet =
				chdir((newDir = _getenv(shellInfo, "PWD=")) ? newDir : "/");
		else
			chdirRet = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argv[1], "-") == 0)
	{
		if (!_getenv(shellInfo, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shellInfo, "OLDPWD=")), _putchar('\n');
		chdirRet =
			chdir((newDir = _getenv(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirRet = chdir(shellInfo->argv[1]);
	if (chdirRet == -1)
	{
		print_error(shellInfo, "can't cd to ");
		_eputs(shellInfo->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(shellInfo, "OLDPWD", _getenv(shellInfo, "PWD="));
		_setenv(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * showHelp - Display help information.
 * @shellInfo: Structure containing potential arguments.
 *
 * This function handles the 'help' command to display help information.
 *
 * Return: Always returns 0.
 */
int showHelp(info_t *shellInfo)
{
	char **argArray;

	argArray = shellInfo->argv;
	_puts("Help: Function not yet implemented\n");
	if (0)
		_puts(*argArray);
	return (0);
}
