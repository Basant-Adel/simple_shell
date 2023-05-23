#include "shell.h"

/**
 * unset_env -> Remove an environment variable
 *
 * @shell: Pointer
 * @var: Pointer
 *
 * Return: Depend Condition
 */

int unset_env(shell_t *shell, char *var)
{
	list_t *node = shell->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			shell->env_changed = delete_node(&(shell->env), i);
			i = 0;
			node = shell->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shell->env_changed);
}
