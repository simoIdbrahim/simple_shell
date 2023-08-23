#include "shell.h"

/**
 * hsh - Main shell function.
 * @information: Pointer to the info structure.
 * @args: Array of strings representing command-line arguments.
 *
 * Return: Exit status.
 */

int hsh(info_t *information, char **args)
{
	ssize_t read_count = 0;
	int builtin_result = 0;

	while (read_count != -1 && builtin_result != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_count = get_input(information);
		if (read_count != -1)
		{
			set_info(information, args);
			builtin_result = find_builtin(information);
			if (builtin_result == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_result == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - Find and execute a built-in command.
 * @information: Pointer to the info structure.
 *
 * Return: Exit status.
 */

int find_builtin(info_t *information)
{
	int i, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(information->argv[0], builtintbl[i].type) == 0)
		{
			information->line_count++;
			built_in_result = builtintbl[i].func(information);
			break;
		}
	return (built_in_result);
}

/**
 * find_cmd - Find and execute a command.
 * @information: Pointer to the info structure.
 */

void find_cmd(info_t *information)
{
	char *path = NULL;
	int i, num_args;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (i = 0, num_args = 0; information->arg[i]; i++)
		if (!is_delim(information->arg[i], " \t\n"))
			num_args++;
	if (!num_args)
		return;

	path = find_path(information, _getenv(information, "PATH="),
			information->argv[0]);
	if (path)
	{
		information->path = path;
		fork_cmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=") ||
		information->argv[0][0] == '/') && is_cmd(information,
		information->argv[0]))
			fork_cmd(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_error(information, "not found\n");
		}
	}
}

/**
 * fork_cmd - Fork and execute a command.
 * @information: Pointer to the info structure.
 */

void fork_cmd(info_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv,
					get_environ(information)) == -1)
		{
			free_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}
