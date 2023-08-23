#include "shell.h"

/**
 * get_history_file - Retrieve the path to the history file.
 * @information: Pointer to the information structure.
 *
 * Return: Pointer to the history file path, or NULL on failure.
 */

char *get_history_file(info_t *information)
{
	char *history_path, *home_dir;

	home_dir = _getenv(information, "HOME=");
	if (!home_dir)
	return (NULL);

	history_path = malloc(sizeof(char) *
		(_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!history_path)
	return (NULL);

	history_path[0] = 0;
	_strcpy(history_path, home_dir);
	_strcat(history_path, "/");
	_strcat(history_path, HIST_FILE);

	return (history_path);
}

/**
 * write_history - Save the history list to the history file.
 * @information: Pointer to the information structure.
 *
 * Return: 1 on success, -1 on failure.
 */

int write_history(info_t *information)
{
	ssize_t file_desc;
	char *file_name = get_history_file(information);
	list_t *current_node = NULL;

	if (!file_name)
	return (-1);

	file_desc = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_desc == -1)
	return (-1);

	for (current_node = information->history; current_node;
			current_node = current_node->next)
	{
	_putsfd(current_node->str, file_desc);
	_putfd('\n', file_desc);
	}
	_putfd(BUF_FLUSH, file_desc);
	close(file_desc);

	return (1);
}

/**
 * read_history - Load history entries from the history file.
 * @information: Pointer to the information structure.
 *
 * Return: Number of history entries read.
 */

int read_history(info_t *information)
{
	int i, last = 0, entry_count = 0;
	ssize_t file_desc, read_len, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *file_name = get_history_file(information);

	if (!file_name)
	return (0);

	file_desc = open(file_name, O_RDONLY);
	free(file_name);
	if (file_desc == -1)
	return (0);

	if (!fstat(file_desc, &file_stat))
	file_size = file_stat.st_size;
	if (file_size < 2)
	return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
	return (0);

	read_len = read(file_desc, buffer, file_size);
	buffer[file_size] = 0;
	if (read_len <= 0)
	{
	free(buffer);
	close(file_desc);
	return (0);
	}
	close(file_desc);

	for (i = 0; i < file_size; i++)
	{
	if (buffer[i] == '\n')
	{
	buffer[i] = 0;
	build_history_list(information, buffer + last, entry_count++);
	last = i + 1;
	}
	}
	if (last != i)
	build_history_list(information, buffer + last, entry_count++);

	free(buffer);
	information->histcount = entry_count;

	while (information->histcount-- >= HIST_MAX)
	delete_node_at_index(&(information->history), 0);

	renumber_history(information);

	return (information->histcount);
}

/**
 * build_history_list - Append an entry to the history linked list.
 * @information: Pointer to the information structure.
 * @entry: Buffer containing the history entry.
 * @entry_count: Entry count for the history entry.
 *
 * Return: 0 on success.
 */

int build_history_list(info_t *information, char *entry, int entry_count)
{
	list_t *node = NULL;

	if (information->history)
	node = information->history;

	add_node_end(&node, entry, entry_count);

	if (!information->history)
	information->history = node;

	return (0);
}

/**
 * renumber_history - Update history entry numbers.
 * @information: Pointer to the information structure.
 *
 * Return: Number of history entries.
 */

int renumber_history(info_t *information)
{
	list_t *node = information->history;
	int i = 0;

	while (node)
	{
	node->num = i++;
	node = node->next;
	}

	return (information->histcount = i);
}
