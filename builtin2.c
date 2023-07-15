#include "shell.h"

/**
 * create_key -generates a new environment variable
 * @vars: Pointer to struct of variables
 *
 * Return: void
 */
void create_key(vars_t *vars)
{
	unsigned int p;
	char **newenv;

	for (p = 0; vars->env[p] != NULL; p++)
		;

	newenv = malloc(sizeof(char *) * (p + 2));
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		exit_new(vars);
	}

	for (p = 0; vars->env[p] != NULL; p++)
		newenv[p] = vars->env[p];

	newenv[p] = add_value(vars->av[1], vars->av[2]);
	if (newenv[p] == NULL)
	{
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(newenv);
		exit(127);
	}

	newenv[p + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * search_key - locates an environment variable
 * @env: Array of environment variables
 * @key: Environment variable to search for
 *
 * Return: Pointer to address of the environment variable
 */
char **search_key(char **env, char *key)
{
	unsigned int p, r, len;

	len = _strlen(key);

	for (p = 0; env[p] != NULL; p++)
	{
		for (r = 0; r < len; r++)
			if (key[r] != env[p][r])
				break;

		if (r == len && env[p][r] == '=')
			return (&env[p]);
	}

	return (NULL);
}

/**
 * create_value - generate a new string for an environment variable
 * @key: Variable name
 * @value: Variable value
 *
 * Return: Points to the new string
 */
char *create_value(char *key, char *value)
{
	unsigned int len1, len2, p, r;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(value);

	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);

	for (p = 0; key[p] != '\0'; p++)
		new[p] = key[p];

	new[p] = '=';

	for (r = 0; value[r] != '\0'; r++)
		new[p + 1 + r] = value[r];

	new[p + 1 + r] = '\0';
	return (new);
}

/**
 * _atoi - Converts a string into an integer
 * @str: String to convert
 *
 * Return: The integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int p, digits;
	int nmb = 0, nmb_test;

	nmb_test = INT_MAX;

	for (digits = 0; nmb_test != 0; digits++)
		nmb_test /= 10;

	for (p = 0; str[p] != '\0' && p < digits; p++)
	{
		nmb *= 10;

		if (str[p] < '0' || str[p] > '9')
			return (-1);

		if ((p == digits - 1) && (str[p] - '0' > INT_MAX % 10))
			return (-1);

		nmb += str[p] - '0';

		if ((p == digits - 2) && (str[p + 1] != '\0') && (nmb > INT_MAX / 10))
			return (-1);
	}

	if (p > digits)
		return (-1);

	return (nmb);
}

