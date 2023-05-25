#include "shell.h"

/**
 * delete_node_alias - unsets an alias in a shell by deleting
 * the corresponding node in the alias linked list
 *@shell: A pointer to a struct
 *@str: A string containing the alias to be unset
 *Return: Always (0)-> Successful, (1)-> ERROR
 */

int delete_node_alias(shell_t *shell, char *str)
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
 * add_update_node_alias - sets an alias in a shell by adding or updating it
 *@shell: struct pointer
 *@str: String containing the alias to be set
 *Return: Always (0)-> Successful, (1)-> ERROR
 */

int add_update_node_alias(shell_t *shell, char *str)
{
	char *b;

	b = _strchr(str, '=');

	if (!b)
	{
		return (1);
	}

	if (!*++b)
	{
		return (delete_node_alias(shell, str));
	}

	delete_node_alias(shell, str);
	return (add_node(&(shell->alias), str, 0) == NULL);
}

/**
 * print_node_alias - A function prints an alias command
 *@node: a pointer to a node in a linked list of strings
 *Return: Always (0)-> Successful, (1)-> ERROR
 */

/**
 * This function prints an alias command in the format "alias 'alias_name=alias_value'".
 * 
 * @param node a pointer to a node in a linked list of strings. Each string in the list is expected to
 * be in the format of an alias definition, where the alias name and its value are separated by an
 * equal sign (=).
 * 
 * @return If the input `node` is not `NULL`, the function returns `0`. Otherwise, it returns `1`.
 */
int print_node_alias(list_t *node)
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
			print_node_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (y = 1; shell->argv[y]; y++)
	{
		b = _strchr(shell->argv[y], '=');

		if (b)
		{
			add_update_node_alias(shell, shell->argv[y]);
		}
		else
		{
			print_node_alias(node_starts_with(shell->alias, shell->argv[y], '='));
		}
	}
	return (0);
}

/**
 * replace_node_alias - A function replaces an alias in the shell's
 * alias list with its corresponding value in the
 * command line arguments.
 *@shell: a pointer to a struct representing the shell environment
 *Return: either 0 or 1
 */

int replace_node_alias(shell_t *shell)
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