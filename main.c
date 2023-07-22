#include "shell.h"

/**
 * main - entry point of the custom shell program.
 * @arg_count: argument count to show number of arguments passed to program.
 * @arg_vector: array of strings containing the arguments passed to program.
 *
 * Return: 0 on successful execution, 1 on error.
 */
int main(int arg_count, char **arg_vector)
{
	CustomShellInfo shell_info[] = {SHELL_INFO_INIT};
	int file_descriptor = 2;

	asm (
		"mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor)
	);

	if (arg_count == 2)
	{
		file_descriptor = open(arg_vector[1], O_RDONLY);

		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arg_vector[0]);
				_eputs(": 0: Can't open ");
				_eputs(arg_vector[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}

		shell_info->read_fd = file_descriptor;
	}

	populate_environment_list(shell_info);
	read_command_history(shell_info);
	custom_shell_main(shell_info, arg_vector);

	return (EXIT_SUCCESS);
}
