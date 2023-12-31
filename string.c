#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of the string
 */
int _strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * _strcmp - performs lexicographic comparison of two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of the next character of haystack or NULL if not found
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (result);
}
