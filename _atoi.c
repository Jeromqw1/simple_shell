#include "shell.h"

/**
* interactive - Facilitates an interactive session with the user.
* @info: A pointer to an info_t structure holding relevant information
* needed for the interactive operations.
*
* Description:
* This function presents a menu of options and performs corresponding actions
* based on the user's choice until the user decides to exit the session.
*
* Note:
* - The info_t structure should be initialized and populated with the
*   necessary data before calling this function.
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - Check if a character is a delimiter.
* @c: The character to check.
* @delim: The delimiter string.
*
* Return: 1 if the character is a delimiter, 0 otherwise.
*/
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}
/**
* _isalpha - Check if a character is an alphabetic character.
* @c: The character to check.
*
* Return: 1 if the character is alphabetic, 0 otherwise.
*/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
* _atoi - Convert a string to an integer.
* @s: The string to be converted.
*
* Return: The converted number if successful, 0 if no numbers in the string.
*/
int _atoi(char *s)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

	if (s[x] >= '0' && s[x] <= '9')
	{
		flag = 1;
		result *= 10;
		result += (s[x] - '0');
	}
	else if (flag == 1)
		flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
