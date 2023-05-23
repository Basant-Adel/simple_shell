#include "shell.h"

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @shell: The shell_t struct, which contains information about
 * the current shell session, such as the current working directory,
 * environment variables, and the command history.
 *  Return: Success return 0, Otherwise, it returns 1
 */

int _setenv(shell_t *shell)
{
	if (shell->argc != 3)
	{
		write_string_char_by_char("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(shell, shell->argv[1], shell->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - unsets environment variables based on the arguments passed to it
 * @shell: a pointer to a struct representing the shell environment
 *  Return: an integer value, which is either 0 or 1
 */

int _unsetenv(shell_t *shell)
{
	int i;

	if (shell->argc == 1)
	{
		write_string_char_by_char("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= shell->argc; i++)
		unset_env(shell, shell->argv[i]);

	return (0);
}

/**
 * set_env -> sets an environment variable with a given value in a shell.
 *
 * @shell: A pointer to a struct representing the shell environment
 * @var: A string representing the name of the environment variable to be set
 * @value: The value to be assigned to the environment variable
 *
 * Return: Success => 0, otherwise => 1
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

/**
 * unset_env -> removes an environment variable from a shell's environment list
 *
 * @shell: a pointer to a shell_t struct
 * @var: The name of the environment variable to unset
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
