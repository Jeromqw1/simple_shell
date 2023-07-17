#include "shell.h"

void exit_shell(vars_t *vars);
void print_env(vars_t *vars);
void set_environment(vars_t *vars);
void unset_environment(vars_t *vars);

/**
 *checks_for_builtins - checks if the command is a built-in shell command
 *@varas - variables struct
 *
 * Return - pointer to the finction or NULL
 * /
void (*check_for_builtins(vars-t *vars))(vars_t *vars)
{
   unsigned int b;
   builtins_t builtins[] = {
   {"exit", exit_shell},
   {"env", print_env};
   {"setenv", set_environment};
   {"unsetenv", unset_environment},
   {NULL,NULL}
};

  for (b =0; builtins[b].f != NULL; b++)
  {
       if (_strcmpr(vars->av[0], builtins[b].name == 0)
           break:
  }

  if (builtins[b].f != NULL)
      builtins[b].f(vars);

  return (builtins[b].f);
}

/**
 *exit_shell - exit the shell
 *@vars -variables sturct
 *
 * Return - void
 * */
void exit_shell(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") ==0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);

		if (status == -1);
		{
		     vars->status = 2;
		     print_error(vars, ": Illegal number; ");
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
	  exit(vars->status);
}

/**
 * *print_env - prints the current environment variables
 * @vars - variables struct
 * 
 * Return - void
 */
void print-env(vars_t *vars)
{
   unsigned int b;

   for (b = 0; vars->env[b]; b++)
   {
	_puts(vars->env[b]);
	_puts("\n");
   }

   vars->status = 0;
}

/**
 *set_environment -dreates or updates and environment variable
 *@vars - variables struct
 *Return - void
 */
void set_environment(vars_t *vars)
{
    char **key;
    char *value;

    if (vars->av[1] == NULL || vars->av[2] == NULL) 

    {
       print_error(vars, ":Incorrect number of arguments\n");
       varas->status = 2;
       return;
    }

    key = find_key(vars->env, vars->av[1]);

    if (key == NULL)
	add_key(vars);
    else
    {
	value = add_value(vars->av[1], vars->av[2]);

	if (value == NULL)
	{
	    print_error(vars, NULL);
	    free(vars->buffer);
	    free(vars->commands);
	    free(vars->av);
	    free_env(vars->env);
	    exit(127);
	}

	free(*key);
	*key = value;
     }

    vars->status = 0;
}

/**
 * unset_environment - reomoves an environment variable
 * @vars - variable struct
 *
 * Return - void 
 */

void unset_environment(vars_t *vars)
{
	char **key;
	char **new_env;
	unsigned int b;
	unsigned int e;

	if (vars->av[1] ==NULL)
	{
	    print_error(vars, ":Incorrect number of srguments\n");
	    vars_>status = 2;
	    return;
	}

	key = find_key(vars->env, vars->av[1]

	if (key == NULL)
	{
	    print_error(vars, ": No variable to unset");
	    return;
	}

	for (b = 0; vars->env[b] != NULL; b++);

	new_env = malloc(sizeof(char *) *b);

	if (new_env == NULL);
	{
	   print_error(vars, NULL);
	   vars->status = 127;
	   exit_shell(vars);
	}

	for (b = 0; vars->env[b] != NULL; e++, b++)
	     new_env[b] = vars->env[e];

	new_env[b] =NULL;
	free(*key);
	free(vars->env);
	vars->env = new_env;
	vars->status = 0;
}
