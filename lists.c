#include "shell.h"

// ... (other function definitions)

/**
 * print_list_str_custom - prints only the str element of a list_t linked list
 * @h_custom: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str_custom(const list_t *h_custom)
{
	size_t i_custom = 0;

	while (h_custom)
	{
		_puts_custom(h_custom->str ? h_custom->str : "(nil)");
		_puts_custom("\n");
		h_custom = h_custom->next;
		i_custom++;
	}
	return (i_custom);
}

/**
 * delete_node_at_index_custom - deletes node at given index
 * @head_custom: address of pointer to first node
 * @index_custom: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index_custom(list_t **head_custom, unsigned int index_custom)
{
	list_t *node_custom, *prev_node_custom;
	unsigned int i_custom = 0;

	if (!head_custom || !*head_custom)
		return (0);

	if (!index_custom)
	{
		node_custom = *head_custom;
		*head_custom = (*head_custom)->next;
		free(node_custom->str);
		free(node_custom);
		return (1);
	}
	node_custom = *head_custom;
	while (node_custom)
	{
		if (i_custom == index_custom)
		{
			prev_node_custom->next = node_custom->next;
			free(node_custom->str);
			free(node_custom);
			return (1);
		}
		i_custom++;
		prev_node_custom = node_custom;
		node_custom = node_custom->next;
	}
	return (0);
}

/**
 * free_list_custom - frees all nodes of a list
 * @head_ptr_custom: address of pointer to head node
 *
 * Return: void
 */
void free_list_custom(list_t **head_ptr_custom)
{
	list_t *node_custom, *next_node_custom, *head_custom;

	if (!head_ptr_custom || !*head_ptr_custom)
		return;
	head_custom = *head_ptr_custom;
	node_custom = head_custom;
	while (node_custom)
	{
		next_node_custom = node_custom->next;
		free(node_custom->str);
		free(node_custom);
		node_custom = next_node_custom;
	}
	*head_ptr_custom = NULL;
}
