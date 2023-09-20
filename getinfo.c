#include "shell.h"

/**
 * clear_info_custom - initializes info_t struct
 * @info_custom: struct address
 */
void clear_info_custom(shell_info_t *info_custom)
{
	info_custom->arg = NULL;
	info_custom->argv = NULL;
	info_custom->path = NULL;
	info_custom->argc = 0;
}

/**
 * set_info_custom - initializes info_t struct
 * @info_custom: struct address
 * @av_custom: argument vector
 */
void set_info_custom(shell_info_t *info_custom, char **av_custom)
{
	int i = 0;

	info_custom->fname = av_custom[0];
	if (info_custom->arg)
	{
		info_custom->argv = strtow(info_custom->arg, " \t");
		if (!info_custom->argv)
		{

			info_custom->argv = malloc(sizeof(char *) * 2);
			if (info_custom->argv)
			{
				info_custom->argv[0] = _strdup(info_custom->arg);
				info_custom->argv[1] = NULL;
			}
		}
		for (i = 0; info_custom->argv && info_custom->argv[i]; i++)
			;
		info_custom->argc = i;

		replace_alias_custom(info_custom);
		replace_vars_custom(info_custom);
	}
}

/**
 * free_info_custom - frees info_t struct fields
 * @info_custom: struct address
 * @all_custom: true if freeing all fields
 */
void free_info_custom(shell_info_t *info_custom, int all_custom)
{
	ffree(info_custom->argv);
	info_custom->argv = NULL;
	info_custom->path = NULL;
	if (all_custom)
	{
		if (!info_custom->cmd_buf)
			free(info_custom->arg);
		if (info_custom->env)
			free_list(&(info_custom->env));
		if (info_custom->history)
			free_list(&(info_custom->history));
		if (info_custom->alias)
			free_list(&(info_custom->alias));
		ffree(info_custom->environ);
		info_custom->environ = NULL;
		bfree((void **)info_custom->cmd_buf);
		if (info_custom->readfd > 2)
			close(info_custom->readfd);
		_putchar(BUF_FLUSH);
	}
}
