#include "shell.h"

/**
 * _myhistory - Display command history
 * @information: Pointer to info_t struct containing history
 * Return: Always 0.
 */

int _myhistory(info_t *information)
{
	print_list(information->history);
	return (0);
}

/**
 * unset_alias - Unset an alias
 * @info: Pointer to info_t struct containing alias
 * @str: Alias to unset
 * Return: Result of the unset operation.
 */

int unset_alias(info_t *info, char *str)
{
	char *pointer, character;
	int result;

	pointer = _strchr(str, '=');
	if (!pointer)
		return (1);
	character = *pointer;
	*pointer = 0;
	result = delete_node_at_index(&(info->alias), 
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pointer = character;
	return (result);
}

/**
 * set_alias - Set an alias
 * @information: Pointer to info_t struct containing alias
 * @string: Alias to set
 * Return: Result of the set operation.
 */

int set_alias(info_t *information, char *string)
{
	char *pointer;

	pointer = _strchr(string, '=');
	if (!pointer)
		return (1);
	if (!*++pointer)
	return (unset_alias(information, string));

	unset_alias(information, string);
	return (add_node_end(&(information->alias), string, 0) == NULL);
}

/**
 * print_alias - Print an alias
 * @current_node: Pointer to the current alias node
 * Return: 0 if successful, 1 if node is NULL.
 */

int print_alias(list_t *current_node)
{
	char *ptr = NULL, *alias_value = NULL;

	if (current_node)
	{
	ptr = _strchr(current_node->str, '=');
	for (alias_value = current_node->str; alias_value <= ptr; alias_value++)
		_putchar(*alias_value);
	_putchar('\'');
	_puts(ptr + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
}

/**
 * _myalias - Display aliases
 * @info: Pointer to info_t struct containing aliases
 * Return: Always 0.
 */

int _myalias(info_t *info)
{
	int index = 0;
	char *ptr = NULL;
	list_t *current_node = NULL;

	if (info->argc == 1)
	{
	current_node = info->alias;
	while (current_node)
	{
		print_alias(current_node);
		current_node = current_node->next;
	}
	return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		ptr = _strchr(info->argv[index], '=');
		if (ptr)
		{
			set_alias(info, info->argv[index]);
		}
		else
		{
			print_alias(node_starts_with(info->alias,
			info->argv[index], '='));
		}
	}

	return (0);
}
