#include "shell.h"

/**
* _myenv - Print the current environment variables.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0.
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
* _getenv - Retrieve the value of an envronment variable.
* @info: Structure containing potential arguments.
* Used to maintain constant function prototype.
* @name: Environment variable name.
* Return: The value of the environment variable or NULL if not found
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
* _mysetenv - Initializes a new environment variable or
* modifies on exiting one
* @info: Structure containing potential arguments.
* Used to maintain constant function prototype
* Return: Always 0.
*/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrent number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return(1);
}
/**
* _myunsetenv - Removes an environment variable.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0.
*/
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}
/**
* populate_env_list - Populates the environment linked list.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0.
*/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
	add_node_end(&node, environ[x], 0);
	info->env = node;
	return (0);
}
/**
* _putfd - Writes the character c to the given file descriptor (fd).
* @c: The character to print.
* @fd: The file descriptor to write to.
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
* _putsfd - Prints an input string to the specified file descriptor (fd).
* @str: The string to be printed.
* @fd: The file descriptor to write to.
*
* Return: The number of characters written.
*/
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
	return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
