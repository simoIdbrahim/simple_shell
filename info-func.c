#include "shell.h"

/**
 * clear_info - Clear the fields of the info structure.
 * @info: Pointer to the info structure.
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Set information in the info structure.
 * @info: Pointer to the info structure.
 * @av: Command-line arguments.
 */

void set_info(info_t *info, char **av)
{
	int loop_index = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (loop_index = 0; info->argv && info->argv[loop_index]; loop_index++)
			;
		info->argc = loop_index;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Free memory and resources in the info structure.
 * @info: Pointer to the info structure.
 * @free_all: Flag to indicate whether to free all resources.
 */

void free_info(info_t *info, int free_all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (free_all)
	{
		if (!info->cmd_buf)
			free(info->arg);

		if (info->env)
			free_list(&(info->env));

		if (info->history)
			free_list(&(info->history));

		if (info->alias)
			free_list(&(info->alias));

		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUF_FLUSH);
	}
}
