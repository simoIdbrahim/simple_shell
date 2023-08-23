#include "shell.h"

/**
 * list_len - prototype func.
 * @h: pnt first NODE.
 * Return: List size.
 */

size_t list_len(const list_t *h)
{
	size_t count;

	for (count = 0; h; h = h->next, ++count)
		;

	return (count);
}

/**
 * list_to_strings - Converts a linked list of strings to an array of strings.
 * @head: ptr first NODE.
 * Return: Arr str.
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t count = list_len(head), count2;
	char **strings;
	char *string;

	if (!head || !count)
	{
		return (NULL);
	}

	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strings)
	{
		return (NULL);
	}

	for (count = 0; node; node = node->next, count++)
	{
		string = (char *)malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (count2 = 0; count2 < count; count2++)
			{
				free(strings[count2]);
			}
			free(strings);
			return (NULL);
		}
		string = _strcpy(string, node->str);
		strings[count] = string;
	}
	strings[count] = NULL;
	return (strings);
}

/**
 * print_list - Prints all elements of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */

size_t print_list(const list_t *h)
{
	size_t i;

	for (i = 0; h; h = h->next, i++)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}

	return (i);
}

/**
 * node_starts_with - Finds a node whose string starts with a prefix.
 * @node: ptr list head.
 * @prefix: str matches.
 * @c: arg next char to prefix arg to matches.
 * Return: Matching NODE or NULL.
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	for (; node; node = node->next)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
		{
			return (node);
		}
	}
	return (NULL);
}

/**
 * get_node_index - Get the ind of a node in the list.
 * @head: arg ptr the list head.
 * @node: arg ptr the node.
 * Return: Ind of node or -1.
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t idx;

	for (idx = 0; head; head = head->next, idx++)
	{
		if (head == node)
		{
			return (idx);
		}
	}

	return (-1);
}
