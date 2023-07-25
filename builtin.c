#include "shell.h"

/**
* _myexit - Exits the shell or sets an error status if invalid exit argument.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
*
* If the 'exit' command is called with an argument, this function attempts
* to convert the argument to an integer and exits the shell with the given
* exit status. If the argument is not a valid integer, it sets an error status
* and displays an error message.
*
* If the 'exit' command is called without an argument, the shell will exit
* with the exit status set to the value of info->err_num.
*
* Return: Always returns -2 to indicate that the shell should exit.
* If info->argv[0] is not "exit", returns 0 to continue shell execution.
*/

int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
* _mycd - Changes the current directory of the process.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
*
* If the 'cd' command is called without an argument, it changes the current
* directory to the home directory
* (retrieved from the environment variable 'HOME').
*
* If the 'cd' command is called with the argument '-', it changes the current
* directory to the previous directory
* (retrieved from the environment variable 'OLDPWD').
*
* If the 'cd' command is called with a valid directory path as an argument,
* it changes the current directory to the specified directory.
*
* Return: Always returns 0 to indicate successful execution.
*/
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
	if (!dir)
		chdir_ret = /* TODO: what should this be? */
		chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
	else
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
		chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
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
	return (0);
}

/**
* _myhelp - Provides basic help information for shell commands.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
*
* This function displays a basic message indicating that the 'help' command
* has been called, but the implementation is not yet provided.
*
* Return: Always returns 0 to indicate successful execution.
*/
int _myhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}
