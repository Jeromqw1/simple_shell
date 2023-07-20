#include "shell.h"

/**
* my_exit - Exits the shell
* @info: Structure containing potential arguments. Used to maintain
* a constant function prototype.
* Return: Exits with a given exit status
* (0) if info->argv[0] != "exit"
*/

int my_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal Number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-1);
	}
	info->err_num = -1;
	return (-2);
}

/**
* change_directory - Changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* a constant function prototype.
* @dir: Pointer to the directory path string
* Return: 0 on success, -1 on failure
*/

int change_directory(info_t *info, char **dir)
{
	char *current_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd fialure emsg here<<\n");

	if (!info->argv[1])
		chdir_ret = change_directory(info, dir);
	else if (_strcmp(info->argv[1], "-") == 0)
		chdir_ret = change_to_previous_directory(info, dir);
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return (-1);
	}
	update_directory_info(info, buffer);
	return (0);
}
/**
* change_to_home_directory - changes the current directory
* to the home directory
* @info: Structure containing potential arguments. Used to maintain
* a constant function prototype.
* @dir: Pointer to the directory path string
* Return: Always 0
*/
int change_to_home_directory(info_t *info, char **dir)
{
	*dir = _getenv(info, "HOME=");
	if (!*dir)
	{
		*dir = _getenv(info, "PWD=");
		if (!*dir)
			*dir = "/";
	}
	return (chdir(*dir));
}

/**
* change_to_previous_directory - Changes the current directory
* to the previous directory
* @info: Structure containing potential arguments. Used to maintain
* a constant function prototype.
* @dir: Pointer to the directory path string
* Return: 0 on success, -1 on failure
*/
int change_to_previous_directory(info_t *info, char **dir)
{
	*dir = _getenv(info, "OLDPWD=");
	if (!*dir)
	{
		_puts(info->current_dir);
		_putchar('\n');
		return (-1);
	}
	_puts(*dir);
	_putchar('\n');
	return (chdir(*dir));
}
/**
* my_cd - Handles the cd built-in command
* @info: Structure containing potential arguments. Used to maintain
*        a constant function prototype.
* Return: Always 0
*/

int my_cd(info_t *info)
{
	char *dir;
	int result;

	result = change_directory(info, &dir);

	if (result != -1)
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(NULL, 0));
	}
	return (0);
}

/**
* my_help - Provides help information
* @info: Structure containing potential arguments. Used to maintain
*         a constant function prototype.
* Return: Always 0
*/
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
