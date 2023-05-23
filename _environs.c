#include "shell.h"

/**
 * print_env - prints the current environment (str only)
 * @shell: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int print_env(shell_t *shell)
{
	while (shell->env)
	{
		_puts(shell->env->str ? shell->env->str : "(nil)");
		_puts("\n");
		shell->env = shell->env->next;
	}
	return (0);
}

/**
 * create_env_list -> Creates a linked list for the environment
 *
 * @shell: Pointer
 *
 * Return: Always 0
 */

int create_env_list(shell_t *shell)
{
	list_t *newEnv = NULL;
  size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node(&newEnv, environ[i], 0);
	}

	shell->env = newEnv;

	return (0);
}

/**
 * get_environ -> Get the environment as an array of strings
 *
 * @shell: Pointer
 *
 * Return: Depend Condition
 */

char **get_environ(shell_t *shell)
{
	if (!shell->environ || shell->env_changed)
	{
		shell->environ = list_to_strings(shell->env);
		shell->env_changed = 0;
	}

	return (shell->environ);
}
