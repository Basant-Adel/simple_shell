#include "shell.h"

/**
 * write_history - creates a file, or appends to an existing file
 * @shell: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int write_history(shell_t *shell)
{
	ssize_t fileDescriptor;
	char *filename = get_history(shell);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileDescriptor == -1)
		return (-1);
	for (node = shell->history; node; node = node->next)
	{
		write_string_to_buffer(node->str, fileDescriptor);
		write_char_to_buffer('\n', fileDescriptor);
	}
	write_char_to_buffer(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);
	return (1);
}

/**
 * build_history_list - adds entry to a history linked list
 * @shell: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_history_list(shell_t *shell, char *buf, int linecount)
{
	list_t *node = NULL;

	if (shell->history)
		node = shell->history;
	add_node(&node, buf, linecount);

	if (!shell->history)
		shell->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @shell: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int renumber_history(shell_t *shell)
{
	list_t *node = shell->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (shell->histcount = i);
}

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
