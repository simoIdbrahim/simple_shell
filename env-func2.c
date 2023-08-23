#include "shell.h"

/**
 * get_environ - Get the environment variables as an array
 * @info: Information structure containing environment data
 *
 * Return: Array of environment variables
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
	info->environ = list_to_strings(info->env);
	info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Unset an environment variable
 * @info: Information structure containing environment data
 * @variable: Variable to unset
 *
 * Return: 1 if unset, 0 otherwise
 */

int _unsetenv(info_t *info, char *variable)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *pointer;

	if (!current_node || !variable)
	return (0);

	while (current_node)
	{
	pointer = starts_with(current_node->str, variable);
	if (pointer && *pointer == '=')
	{
		info->env_changed = delete_node_at_index(&(info->env), index);
		index = 0;
		current_node = info->env;
	continue;
	}
	current_node = current_node->next;
	index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Set an environment variable
 * @info: Information structure containing environment data
 * @variable: Variable to set
 * @value: Value to set for the variable
 *
 * Return: 1 on success, 0 on failure
 */

int _setenv(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *pointer;

	if (!variable || !value)
	return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
	return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	current_node = info->env;
	while (current_node)
	{
	pointer = starts_with(current_node->str, variable);
	if (pointer && *pointer == '=')
	{
		free(current_node->str);
		current_node->str = buffer;
		info->env_changed = 1;
	return (0);
	}
	current_node = current_node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
