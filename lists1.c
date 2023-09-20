#include "shell.h"

/**
 * list_len_custom - determines length of linked list
 * @h_custom: pointer to first node
 *
 * Return: size of list
 */
size_t list_len_custom(const list_t *h_custom)
{
	size_t i_custom = 0;

	while (h_custom)
	{
		h_custom = h_custom->next;
		i_custom++;
	}
	return (i_custom);
}

/**
 * list_to_strings_custom - returns an array of strings of the list->str_custom
 * @head_custom: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings_custom(list_t *head_custom)
{
	list_t *node_custom = head_custom;
	size_t i_custom = list_len_custom(head_custom), j_custom;
	char **strs_custom;
	char *str_custom;

	if (!head_custom || !i_custom)
		return (NULL);
	strs_custom = malloc(sizeof(char *) * (i_custom + 1));
	if (!strs_custom)
		return (NULL);
	for (i_custom = 0; node_custom; node_custom = node_custom->next, i_custom++)
	{
		str_custom = malloc(_strlen(node_custom->str) + 1);
		if (!str_custom)
		{
			for (j_custom = 0; j_custom < i_custom; j_custom++)
				free(strs_custom[j_custom]);
			free(strs_custom);
			return (NULL);
		}

		str_custom = _strcpy(str_custom, node_custom->str);
		strs_custom[i_custom] = str_custom;
	}
	strs_custom[i_custom] = NULL;
	return (strs_custom);
}

/**
 * print_list_custom - prints all elements of a list_t linked list
 * @h_custom: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_custom(const list_t *h_custom)
{
	size_t i_custom = 0;

	while (h_custom)
	{
		_puts_custom(convert_number(h_custom->num, 10, 0));
		_putchar_custom(':');
		_putchar_custom(' ');
		_puts_custom(h_custom->str ? h_custom->str : "(nil)");
		_puts_custom("\n");
		h_custom = h_custom->next;
		i_custom++;
	}
	return (i_custom);
}

/**
 * node_starts_with_custom - returns node whose string starts with prefix
 * @node_custom: pointer to list head
 * @prefix_custom: string to match
 * @c_custom: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with_custom(list_t *node_custom, char *prefix_custom, char c_custom)
{
	char *p_custom = NULL;

	while (node_custom)
	{
		p_custom = starts_with(node_custom->str, prefix_custom);
		if (p_custom && ((c_custom == -1) || (*p_custom == c_custom)))
			return (node_custom);
		node_custom = node_custom->next;
	}
	return (NULL);
}

/**
 * get_node_index_custom - gets the index of a node
 * @head_custom: pointer to list head
 * @node_custom: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index_custom(list_t *head_custom, list_t *node_custom)
{
	size_t i_custom = 0;

	while (head_custom)
	{
		if (head_custom == node_custom)
			return (i_custom);
		head_custom = head_custom->next;
		i_custom++;
	}
	return (-1);
}
