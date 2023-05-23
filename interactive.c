#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @shell: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int interactive(shell_t *shell)
{
	return (isatty(STDIN_FILENO) && shell->fileDescriptor <= 2);
}
