#include "shell.h"

/**
 * is_command_executable - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command_executable(shell_info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return 0;

	if (st.st_mode & S_IFREG)
	{
		return 1;
	}
	return 0;
}

/**
 * duplicate_characters - duplicates characters
 * @path_string: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *path_string, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_string[i] != ':')
			buffer[k++] = path_string[i];
	buffer[k] = 0;
	return buffer;
}

/**
 * find_command_in_path - finds this command in the PATH string
 * @info: the info struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_command_in_path(shell_info_t *info, char *path_string, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_string)
		return NULL;
	if ((strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_command_executable(info, command))
			return command;
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = duplicate_characters(path_string, current_position, i);
			if (!*path)
				strcat(path, command);
			else
			{
				strcat(path, "/");
				strcat(path, command);
			}
			if (is_command_executable(info, path))
				return path;
			if (!path_string[i])
				break;
			current_position = i;
		}
		i++;
	}
	return NULL;
}
