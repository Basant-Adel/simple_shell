#include "shell.h"

/**
 * replace_shell_vars - replaces vars in the tokenized string
 * @shell: a pointer to a struct
 *
 * Return: 0
 */

int replace_shell_vars(shell_t *shell)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell->argv[i]; i++)
	{
		if (shell->argv[i][0] != '$' || !shell->argv[i][1])
			continue;

		if (!_strcmp(shell->argv[i], "$?"))
		{
			replace_string_shell_vars(&(shell->argv[i]),
				_strdup(convert_num(shell->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shell->argv[i], "$$"))
		{
			replace_string_shell_vars(&(shell->argv[i]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(shell->env, &shell->argv[i][1], '=');
		if (node)
		{
			replace_string_shell_vars(&(shell->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string_shell_vars(&shell->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string_shell_vars -> Replace a string with a new one
 *
 * @old: old Pointer
 * @new: new Pointer
 *
 * Return: 1
 */

int replace_string_shell_vars(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
