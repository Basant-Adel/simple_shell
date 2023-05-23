#include "shell.h"

/**
 * print_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @shell: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int print_history(shell_t *shell)
{
	while (shell->history)
	{
		_puts(convert_num(shell->history->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(shell->history->str ? shell->history->str : "(nil)");
		_puts("\n");
		shell->history = shell->history->next;
	}
	return (0);
}
