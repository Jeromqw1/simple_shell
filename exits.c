#include "shell.h"

/**
* _strncpy - Copies a string up to a specified number of characters.
* @dest: The destination string to copy to.
* @src: The source string to be copied from.
* @n: The maximum number of characters to be copied.
*
* This function copies at most 'n' characters from the source string 'src'
* to the destination string 'dest'. If the length of 'src' is less than 'n',
* the remaining characters in 'dest' will be filled with null bytes.
* The destination string 'dest' must be large enough to hold 'n' characters
* and a null-terminating byte.
*
* Return: A pointer to the destination string 'dest'.
*/
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
* _strncat - Concatenates two strings up to a specified number of bytes.
* @dest: The first string (destination)
* where the other string will be appended.
* @src: The second string (source) to be appended.
* @n: The maximum number of bytes to be used from 'src'.
*
* This function appends at most 'n' bytes from the source string 'src'
* to the destination string 'dest'. The destination string 'dest' must be
* large enough to hold the concatenated result. The resulting string in 'dest'
* will always be null-terminated, even if the maximum number of bytes 'n' is
* reached before the end of 'src'.
*
* Return: A pointer to the destination string 'dest'.
*/
char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
		return (s);
}

/**
* _strchr - Locates a character in a string.
* @s: The string to be parsed.
* @c: The character to look for.
*
* This function searches for the first occurrence of the character 'c' in
* the string 's'. If 'c' is found, a pointer to the first occurrence of 'c'
* in 's' is returned. If 'c' is not found, NULL is returned.
*
* Return: A pointer to the first occurrence of 'c' in 's' or NULL if not found.
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');

	return (NULL);
}
