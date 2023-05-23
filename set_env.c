#include "shell.h"

/**
 * set_env -> Set an environment variable
 *
 * @shell: Pointer
 * @var: Pointer
 * @value: Pointer
 *
 * Return: Depend Condition
 */

int set_env(shell_t *shell, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = shell->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shell->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node(&(shell->env), buf, 0);
	free(buf);
	shell->env_changed = 1;
	return (0);
}
