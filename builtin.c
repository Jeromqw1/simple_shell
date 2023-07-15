#include "shell.h"

/**
 * check_for_builtins - Checks if the command is a builtin
 * @vars: Variables
 * Return: Pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int p;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (p = 0; check[p].f != NULL; p++)
	{
		if (_strcmpr(vars->av[0], check[p].name) == 0)
			break;
	}

	if (check[p].f != NULL)
		check[p].f(vars);

	return (check[p].f);
}

/**
 * new_exit - Exits the program
 * @vars: Variables
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}

	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * _env - Prints the environment currently used
 * @vars: Struct of variables
 * Return: void
 */
void _env(vars_t *vars)
{
	unsigned int p;

	for (p = 0; vars->env[p]; p++)
	{
		_puts(vars->env[p]);
		_puts("\n");
	}

	vars->status = 0;
}

/**
 * new_setenv - Creates a new environment variable or edits an existing variable
 * @vars: Pointer to struct of variables
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}

	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}

	vars->status = 0;
}

/**
 * new_unsetenv - Removes an environment variable
 * @vars: Pointer to a struct of variables
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;
	unsigned int p, r;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}

	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}

	for (p = 0; vars->env[p] != NULL; p++)
		;

	newenv = malloc(sizeof(char *) * p);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}

	for (p = 0; vars->env[p] != *key; p++)
		newenv[p] = vars->env[p];

	for (r = p + 1; vars->env[r] != NULL; r++, p++)
		newenv[p] = vars->env[r];

	newenv[p] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
