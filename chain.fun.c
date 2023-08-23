#include "shell.h"

/**
 * is_chain - Checks if there is a command chain present
 * @info: Pointer to info_t structure
 * @buffer: Command buffer
 * @position: Pointer to the current position in buffer
 * Return: 1 if command chain found, 0 otherwise
 */

int is_chain(info_t *info, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
	buffer[j] = 0;
	j++;
	info->command_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
	buffer[j] = 0;
	j++;
	info->command_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
	buffer[j] = 0;
	info->command_buffer_type = CMD_CHAIN;
	}
	else
	return (0);
	*position = j;
	return (1);
}

/**
 * check_chain - Checks the command chain type and updates buffer position
 * @info: Pointer to info_t structure
 * @buffer: Command buffer
 * @position: Pointer to the current position in buffer
 * @i: Current index
 * @length: Length of the buffer
 */

void check_chain(info_t *info, char *buffer,
		size_t *position, size_t i, size_t length)
{
	size_t j = *position;

	if (info->command_buffer_type == CMD_AND)
	{
		if (info->status)
		{
		buffer[i] = 0;
		j = length;
		}
	}
	if (info->command_buffer_type == CMD_OR)
	{
	if (!info->status)
		{
		buffer[i] = 0;
		j = length;
		}
	}

	*position = j;
}

/**
 * replace_alias - Replaces command with alias if found
 * @info: Pointer to info_t structure
 * Return: 1 if successful, 0 otherwise
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
	node = node_starts_with(info->alias, info->arguments[0], '=');
	if (!node)
		return (0);
	free(info->arguments[0]);
	ptr = _strchr(node->str, '=');
	if (!ptr)
		return (0);
	ptr = _strdup(ptr + 1);
	if (!ptr)
		return (0);
	info->arguments[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in arguments
 * @info: Pointer to info_t structure
 * Return: Always 0.
 */

int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->arguments[i]; i++)
	{
	if (info->arguments[i][0] != '$' || !info->arguments[i][1])
		continue;

	if (!_strcmp(info->arguments[i], "$?"))
	{
		replace_string(&(info->arguments[i]),
			_strdup(convert_number(info->status, 10, 0)));
		continue;
	}
	if (!_strcmp(info->arguments[i], "$$"))
	{
		replace_string(&(info->arguments[i]),
			_strdup(convert_number(getpid(), 10, 0)));
		continue;
	}
	node = node_starts_with(info->env, &info->arguments[i][1], '=');
	if (node)
	{
		replace_string(&(info->arguments[i]),
			_strdup(_strchr(node->str, '=') + 1));
	continue;
	}
	replace_string(&info->arguments[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replaces a string with a new one
 * @old: Pointer to the old string
 * @new: New string
 * Return: 1 if successful, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
