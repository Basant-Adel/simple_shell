#include "shell.h"

/**
 * print_env - prints the current environment variables stored
 * in a linked list (str only)
 * @shell: a pointer to a struct of type "shell_t"
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
 * create_env_list -> creates a linked list of environment variables
 * from the global variable "environ" and
 * assigns it to the "env" member of the "shell" struct.
 *
 * @shell: a pointer to a struct of type "shell_t"
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
 * get_environ -> returns a pointer to the environment variables of a shell
 * converting them from a linked list to an array of strings if necessary.
 *
 * @shell: A pointer to a struct representing the shell environment
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

/**
 * get_env - searches for a specific environment variable
 * in a linked list and returns its value
 * @shell: A pointer to a struct representing the shell environment
 * @name: The name of the environment variable to search for
 *
 * Return: a pointer to the value of the environment variable with the
 * given name or NULL
 */

char *get_env(shell_t *shell, const char *name)
{
	list_t *node = shell->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
