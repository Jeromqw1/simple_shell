#include "shell.h"

/**
* input_buf - Buffers chained commands and reads input from STDIN.
* @info: Parameter struct containing shell information.
* @buf: Address of the buffer where the input will be stored.
* @len: Address of the length variable to track the buffer size.
*
* This function reads input from STDIN and buffers chained commands
* separated by semicolons. It handles command chaining and removes comments
* from the input. If the buffer is not empty, it continues reading from the
* previous position to handle command chaining. The buffered command is
* passed back through the 'buf' parameter, and its length is tracked in 'len'.
*
* Return: The number of bytes read from STDIN.
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
		#else
		r = _getline(info, buf, &len_p);
		#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
* get_input - Reads a line from STDIN and handles command chaining.
* @info: Parameter struct containing shell information.
*
* This function reads a line of input from STDIN and handles command chaining
* by buffering the input and processing commands separated by semicolons.
* It checks for command chaining and returns the length of the current command.
*
* Return: The number of bytes read from STDIN.
*/
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar('\n');
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i;
		p = buf + i;

		void check_chain(info, buf, j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
* read_buf - Reads a buffer from the file descriptor.
* @info: Parameter struct containing shell information.
* @buf: Buffer to store the read data.
* @i: Size of the buffer.
*
* Return: The number of bytes read, or 0 if the buffer is not empty.
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
	return (0);
	r = read(info->readfd, buf, READ_BUT_SIZE);
	if (r >= 0)
	*i = r;
	return (r);
}

/**
* _getline - Gets the next line of input from STDIN.
* @info: Parameter struct containing shell information.
* @ptr: Address of pointer to buffer, preallocated or NULL.
* @length: Size of preallocated ptr buffer if not NULL.
*
* This function reads the next line of input from STDIN. If a preallocated
* buffer is provided, it appends the input to it. Otherwise, it allocates
* memory for the buffer. The function handles command chaining and returns
* the length of the input line (excluding the newline character).
*
* Return: The length of the input line (excluding newline character).
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUT_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
	s = *length;
	if (i == len)
	i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
	return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
	return (p ? free(p), -1 : -1);

	if (s)
	_strncat(new_p, buf + i, k - i);
	else
	_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
	*length = s;
	*ptr = p;
	return (s);
}

/**
* sigintHandler - Blocks Ctrl-C (SIGINT) and handles the signal.
* @sig_num: The signal number (unused in this function).
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar('\n');
}
