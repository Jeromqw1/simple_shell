#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @b: points to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *b)
{
	size_t u = 0;

	while (b)
	{
		b = b->next;
		u++;
	}
	(return u);
}

/**
 * list_to_strings - returns an array of strings from the list->str
 * @head: points to first node
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t u = list_len(head), v;
	char **strs;
	char *str;

	if (!head || !u)
		(return NULL);

	strs = malloc(sizeof(char *) * (u + 1));
	if (!strs)
		(return NULL);

	for (u = 0; node; node = node->next, u++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (v = 0; v < u; v++)
				free(strs[v]);
			free(strs);
			(return NULL);
		}
		str = _strcpy(str, node->str);
		strs[u] = str;
	}
	strs[u] = NULL;
	(return strs);
}

/**
 * print_list - prints all elements of a linked list
 * @b: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *b)
{
	size_t u = 0;

	while (b)
	{
		_puts(convert_number(b->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(b->str ? b->str : "(nil)");
		_puts("\n");
		b = b->next;
		u++;
	}
	(return u);
}

/**
 * node_starts_with - returns the node whose string starts with a prefix
 * @node: points to the list head
 * @prefix: string to match
 * @a: next character after the prefix to match
 *
 * Return: Matching node or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char a)
{
	char *k = NULL;

	while (node)
	{
		k = starts_with(node->str, prefix);
		if (k && ((a == -1) || (*k == a)))
			(return node);
		node = node->next;
	}
	(return NULL);
}

/**
 * get_node_index - gets the index of the node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: Index of the node or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t u = 0;

	while (head)
	{
		if (head == node)
			(return u);
		head = head->next;
		u++;
	}
	(return -1);
}
