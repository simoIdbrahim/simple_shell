#include "shell.h"

/**
 * add_node - Adds a NODE to the beginning of the list
 * @head: Addr pointer to head NODE
 * @str: String field of NODE
 * @num: Node index used by history
 * Return: Size of the list NODE.
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newNode;

	if (!head)
	{
		return (NULL);
	}
	newNode = malloc(sizeof(list_t));
	if (!newNode)
	{
		return (NULL);
	}
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * add_node_end - Adds a NODE to the end
 * @head: Addr pointer to the head NODE
 * @str: String field of the NODE
 * @num: Node ind using for history
 * Return: Address of the new NODE, or NULL on failure
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	newNode = malloc(sizeof(list_t));

	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 * print_str_list - Print element of list_t linked list
 * @h: ptr to first NODE
 * Return: Size list
 */

size_t print_str_list(const list_t *h)
{
	size_t ind = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ind++;
	}
	return (ind);
}

/**
 * delete_node_at_index - Deletes the NODE ind
 * @head: Address of a pointer to the first node
 * @index: Index of the node to delete
 * Return: 1 if true, 0 if false
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int start = 0;

	if (!head || !*head)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (start == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		start++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all
 * @head_ptr: Addr of a ptr to the NODE
 * Return: NONE
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *nextNode, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	node = head;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	*head_ptr = NULL;
}

