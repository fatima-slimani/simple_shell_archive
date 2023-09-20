#include "shell.h"

/**
 * myexit - exits the shell
 * @info: Structure containing potential arguments.
 *         Used to maintain a constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit"
 */
int myexit(shell_info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return 1;
		}
		info->err_num = _erratoi(info->argv[1]);
		return -2;
	}
	info->err_num = -1;
	return -2;
}

/**
 * mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *         Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int mycd(shell_info_t *info)
{
	char *current_path, *new_path, buffer[1024];
	int chdir_ret;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		new_path = _getenv(info, "HOME=");
		if (!new_path)
			chdir_ret = chdir((new_path = _getenv(info, "PWD=")) ? new_path : "/");
		else
			chdir_ret = chdir(new_path);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return 1;
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((new_path = _getenv(info, "OLDPWD=")) ? new_path : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * myhelp - displays help information (function not yet implemented)
 * @info: Structure containing potential arguments.
 *         Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int myhelp(shell_info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return 0;
}
