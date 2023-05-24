#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @shell: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(shell_t *shell, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		shell->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		shell->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		shell->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @shell: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(shell_t *shell, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (shell->cmd_buf_type == CMD_AND)
	{
		if (shell->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (shell->cmd_buf_type == CMD_OR)
	{
		if (!shell->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}
