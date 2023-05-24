#include "shell.h"

/**
 * unsetalias - A function to unsets alias to string
 *@shell: It's a parameter (struct)
 *@str: String
 *Return: Always (0)-> Successful, (1)-> ERROR
 */

int unsetalias(shell_t *shell, char *str)
{
	char *b, v;
	int get;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	v = *b;
	*b = 0;
	get = delete_node(&(shell->alias),
		get_index_node(shell->alias, node_starts_with(shell->alias, str, -1)));
	*b = v;
	return (get);
}

/**
 * setalias - A function to sets alias to string
 *@shell: It's a parameter (struct)
 *@str: String
 *Return: Always (0)-> Successful, (1)-> ERROR
 */

int setalias(shell_t *shell, char *str)
{
	char *b;

	b = _strchr(str, '=');

	if (!b)
	{
		return (1);
	}

	if (!*++b)
	{
		return (unsetalias(shell, str));
	}

	unsetalias(shell, str);
	return (add_node(&(shell->alias), str, 0) == NULL);
}

/**
 * printalias - A function to print an alias string
 *@node: It's an alias node
 *Return: Always (0)-> Successful, (1)-> ERROR
 */

int printalias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - A function to Implement the alias builtin command
 *@shell: Structure containing potential arguments
 *Used to maintain constant function prototype
 *Return: Always (0)-> Successful
 */

int _alias(shell_t *shell)
{
	int y = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (shell->argc == 1)
	{
		node = shell->alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (y = 1; shell->argv[y]; y++)
	{
		b = _strchr(shell->argv[y], '=');

		if (b)
		{
			setalias(shell, shell->argv[y]);
		}
		else
		{
			printalias(node_starts_with(shell->alias, shell->argv[y], '='));
		}
	}
	return (0);
}

/**
 * replacealias - A function to replace an alias in tokenized string
 *@shell: It's a parameter (struct)
 *Return: Give (1)-> for Replaced, (0) for Otherwise
 */

int replacealias(shell_t *shell)
{
	int y;
	list_t *node;
	char *b;

	for (y = 0; y < 10; y++)
	{
		node = node_starts_with(shell->alias, shell->argv[0], '=');

		if (!node)
		{
			return (0);
		}
		free(shell->argv[0]);
		b = _strchr(node->str, '=');

		if (!b)
		{
			return (0);
		}
		b = _strdup(b + 1);

		if (!b)
		{
			return (0);
		}
		shell->argv[0] = b;
	}
	return (1);
}
