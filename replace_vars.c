#include "shell.h"

/**
 * replace_vars - replaces vars in the tokenized string
 * @shell: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(shell_t *shell)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell->argv[i]; i++)
	{
		if (shell->argv[i][0] != '$' || !shell->argv[i][1])
			continue;

		if (!_strcmp(shell->argv[i], "$?"))
		{
			replace_string(&(shell->argv[i]),
				_strdup(convert_num(shell->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shell->argv[i], "$$"))
		{
			replace_string(&(shell->argv[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(shell->env, &shell->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shell->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&shell->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string -> Replace a string with another
 *
 * @old: Pointer
 * @new: Pointer
 *
 * Return: Depend Condition
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
