#include "shell.h"

/**
 * _myexit - Handles the exit command.
 * @info: Pointer to the info_t structure.
 *
 * Return: 1 on error, -2 on successful exit.
 */

int _myexit(info_t *info)
{
	int exit;

	if (info->argv[1])
	{
		exit = _erratoi(info->argv[1]);
		if (exit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Handles the cd command.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always returns 0.
 */

int _mycd(info_t *info)
{
	char *targetDir, buffer[1024];
	char *currentPath = getcwd(buffer, sizeof(buffer));
	int chdirResult = -1;

	if (!currentPath)
		_puts("TODO: >>getcwd failure message here<<\n");

	if (info->argv[1])
	{
		if (_strcmp(info->argv[1], "-") == 0)
		{
			targetDir = _getenv(info, "OLDPWD=");
			if (targetDir)
			{
				_puts(targetDir);
				_putchar('\n');
				chdirResult = chdir(targetDir);
			}
		}
		else
		{
			targetDir = info->argv[1];
			chdirResult = chdir(targetDir);
		}
	}
	else
	{
		targetDir = _getenv(info, "HOME=");
		if (!targetDir)
			targetDir = _getenv(info, "PWD=");

		if (targetDir)
			chdirResult = chdir(targetDir);
	}

	if (chdirResult == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(targetDir);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", currentPath);
		_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}

	return (0);
}

/**
 * _myhelp - Handles the help command.
 * @information: Pointer to the info_t structure.
 *
 * Return: Always returns 0.
 */

int _myhelp(info_t *information)
{
	char **arguments = information->argv;

	_puts("Help call executed successfully. Implementation pending.\n");

	if (0)
	_puts(*arguments);

	return (0);
}
