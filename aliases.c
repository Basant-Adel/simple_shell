#include "shell.h"

/**
 * unset_alias - sets alias to string
 * @shell: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(shell_t *shell, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node(&(shell->alias),
		get_index_node(shell->alias, node_starts_with(shell->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @shell: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int set_alias(shell_t *shell, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(shell, str));

	unset_alias(shell, str);
	return (add_node(&(shell->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @shell: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _alias(shell_t *shell)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (shell->argc == 1)
	{
		node = shell->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell->argv[i]; i++)
	{
		p = _strchr(shell->argv[i], '=');
		if (p)
			set_alias(shell, shell->argv[i]);
		else
			print_alias(node_starts_with(shell->alias, shell->argv[i], '='));
	}

	return (0);
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @shell: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_alias(shell_t *shell)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(shell->alias, shell->argv[0], '=');
		if (!node)
			return (0);
		free(shell->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		shell->argv[0] = p;
	}
	return (1);
}
