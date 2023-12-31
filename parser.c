#include "shell.h"

/**
 * is_cmd -determines if a file is an executable command
 * @info: pointer to the info struct
 * @path: path to the file
 *
 * Return: 1 if the file is executabe command, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * dup_chars - replica characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer of the replicated characters
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int u = 0, v = 0;

	for (v = 0, u = start; u < stop; u++)
	{
		if (pathstr[u] != ':')
			buf[v++] = pathstr[u];
	}

	buf[v] = 0;
	return (buf);
}

/**
 * find_path - finds the given cmd in the PATH string
 * @info: points to the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of the cmd if found, otherwise NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int u = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[u] || pathstr[u] == ':')
		{
			path = dup_chars(pathstr, curr_pos, u);

			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_cmd(info, path))
				return (path);

			if (!pathstr[u])
				break;

			curr_pos = u;
		}
		u++;
	}

	return (NULL);
}
