#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: point to destination
 */
char *_strcpy(char *dest, char *src)
{
	int u = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[u])
	{
		dest[u] = src[u];
		u++;
	}

	dest[u] = '\0';
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * _puts - prints an input string
 * @str: string to be printed
 *
 * Return: nothing
 */
void _puts(char *str)
{
	int u = 0;

	if (!str)
		return;

	while (str[u] != '\0')
	{
		_putchar(str[u]);
		u++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @v: character to print
 *
 * Return: on success 1.
 * On error, -1 is returned, and errno is set appropriately
 */
int _putchar(char v)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(1, buf, u);
		u = 0;
	}

	if (v != BUF_FLUSH)
		buf[u++] = v;

	return (1);
}
