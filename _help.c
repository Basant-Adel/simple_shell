#include "shell.h"

/**
 * _help - changes the current directory of the process
 * @shell: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

/* TODO */
int _help(shell_t *shell)
{
	char **arg_array;

	arg_array = shell->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
