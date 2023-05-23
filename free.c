#include "shell.h"

/**
 * free_str -> Free string
 *
 * @pp: Pointer
 */

void free_str(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * free_ptr -> Frees a pointer
 *
 * @ptr: Pointer
 *
 * Return: Depend Condition
 */

int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_list -> Free list
 *
 * @head_ptr: Pointer
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * free_shell -> Free shell
 *
 * @shell: Pointer
 * @all: Depend Condition
 */

void free_shell(shell_t *shell, int all)
{
	free_str(shell->argv);
	shell->argv = NULL;
	shell->path = NULL;
	if (all)
	{
		if (!shell->cmd_buf)
			free(shell->arg);
		if (shell->env)
			free_list(&(shell->env));
		if (shell->history)
			free_list(&(shell->history));
		if (shell->alias)
			free_list(&(shell->alias));
		free_str(shell->environ);
			shell->environ = NULL;
		free_ptr((void **)shell->cmd_buf);
		if (shell->fileDescriptor > 2)
			close(shell->fileDescriptor);
		_putchar(BUF_FLUSH);
	}
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
