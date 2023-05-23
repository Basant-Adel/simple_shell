#include "shell.h"

/**
 * shell_loop -> Main Loop
 *
 * @shell: shell Struct Pointer
 * @argv: Argument Vector
 *
 * Return: 0 Success, -1 Failure
 */

int shell_loop(shell_t *shell, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_shell(shell);
		if (interactive(shell))
			_puts("$ ");
		put_char(BUF_FLUSH);
		r = get_input(shell);
		if (r != -1)
		{
			init_shell(shell, argv);
			builtin_ret = get_built_in_command(shell);
			if (builtin_ret == -1)
				find_cmd(shell);
		}
		else if (interactive(shell))
			_putchar('\n');
		free_shell(shell, 0);
	}
	write_history(shell);
	free_shell(shell, 1);
	if (!interactive(shell) && shell->status)
		exit(shell->status);
	if (builtin_ret == -2)
	{
		if (shell->err_num == -1)
			exit(shell->status);
		exit(shell->err_num);
	} return (builtin_ret);
}
