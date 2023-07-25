#include "shell.h"

/**
* is_chain - test if the current char in the buffer is a chain delimiter
* @info: parameter struct
* @buf: character buffer
* @a: address of current position in buf
*
* Return: 1 if chain delimiter, 0 otherwise
*/
int is_chain(info_t *info, char *buf, size_t *a)
{
    size_t m = *a;
    if (buf[m] == '|' && buf[m + 1] == '|')
    {
        buf[m] = 0;
        m++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[m] == '&' && buf[m + 1] == '&')
    {
        buf[m] = 0;
        m++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[m] == ';') /* found the end of this command */
    {
        buf[m] = 0; /* replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *a = m;
    return (1);
}

/**
* check_chain - check if I should continue chaining based on last status
* @info: parameter struct
* @buf: character buffer
* @a: address of ma current position in buf
* @b: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *a, size_t b, size_t len)
{
    size_t m = *a;
    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[b] = 0;
            m = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[b] = 0;
            m = len;
        }
    }
    *a = m;
}

/**
* replace_alias - replace the alias in the tokenized string
* @info: parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
    int a;
    list_t *node;
    char *b;
    for (a = 0; a < 10; a++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);

        b = _strchr(node->str, '=');
        if (!b)
            return (0);
        b = _strdup(b + 1);
        if (!b)
            return (0);
        info->argv[0] = b;
    }
    return (1);
}

/**
* replace_vars - replace variable in the tokenized string
* @info: parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *info)
{
    int a = 0;
    list_t *node;
    for (a = 0; info->argv[a]; a++)
    {
        if (info->argv[a][0] != '$' || !info->argv[a][1])
            continue;
        if (!_strcmp(info->argv[a], "$?"))
        {
            replace_string(&(info->argv[a]), _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[a], "$$"))
        {
            replace_string(&(info->argv[a]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->argv[a][1], '=');
        if (node)
        {
            replace_string(&(info->argv[a]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[a], _strdup(""));
    }
    return (0);
}

/**
* replace_string - replace the string
* @a: address of my old string
* @b: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **a, char *b)
{
    free(*a);
    *a = b;
    return (1);
}
