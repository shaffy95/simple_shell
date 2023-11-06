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
			printError(shellInfo, "Illegal number: ");
			shell_eputs(shellInfo->argv[1]);
			shell_eputchar('\n');
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
		shell_puts("TODO: Handle getcwd failure message here\n");
	if (!shellInfo->argv[1])
	{
		newDir = getenv(shellInfo, "HOME=");
		if (!newDir)
			chdirRet = chdir((newDir = getenv(shellInfo, "PWD=")) ? newDir : "/");
		else
			chdirRet = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argv[1], "-") == 0)
	{
		if (!getenv(shellInfo, "OLDPWD="))
		{
			shell_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		shell_puts(getenv(shellInfo, "OLDPWD="));
		_putchar('\n');
		chdirRet = chdir((newDir = getenv(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirRet = chdir(shellInfo->argv[1]);
	if (chdirRet == -1)
	{
		printError(shellInfo, "can't cd to ");
		shell_eputs(shellInfo->argv[1]);
		shell_eputchar('\n');
	}
	else
	{
		setenv(shellInfo, "OLDPWD", getenv(shellInfo, "PWD="));
		setenv(shellInfo, "PWD", getcwd(buffer, 1024));
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
	shell_puts("Help: Function not yet implemented\n");
	if (0)
		shell_puts(*argArray); /* Temporary unused variable workaround */
	return (0);
}
