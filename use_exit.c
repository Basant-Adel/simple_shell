#include "shell.h"

/**
 * use_exit - exits the shell
 * @shell: Structure containing some arguments.
 *  Return: exits with a given exit status
 *  (0) if shell.argv[0] != "exit"
 */

int use_exit(shell_t *shell)
{
	int exitcheck;

	if (shell->argv[1])
	{
		exitcheck = _erratoi(shell->argv[1]);
		if (exitcheck == -1)
		{
			shell->status = 2;
			print_error(shell, "Illegal number: ");
			put_string(shell->argv[1]);
			put_char('\n');
			return (1);
		}
		shell->err_num = _erratoi(shell->argv[1]);
		return (-2);
	}
	shell->err_num = -1;
	return (-2);
}