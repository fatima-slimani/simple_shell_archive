#include "shell.h"

typedef struct
{
	// Other fields you may have in the structure
	list_t *custom_alias; // Adding the custom_alias field
						  // Other fields you may have in the structure
} passinfo;

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int my_env(shell_info_t *info)
{
	print_list_str(info->env);
	return 0;
}

/**
 * get_env - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 *         Used to maintain constant function prototype.
 * @name: environment variable name
 *
 * Return: the value of the environment variable
 */
char *get_env(shell_info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return p;
		node = node->next;
	}
	return NULL;
}

/**
 * my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int my_setenv(shell_info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return 1;
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return 0;
	return 1;
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *         Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int my_unsetenv(shell_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return 1;
	}

	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return 0;
}

/**
 * populate_env_list - populates environment linked list
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int populate_env_list(shell_info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);

	info->env = node;
	return 0;
}
