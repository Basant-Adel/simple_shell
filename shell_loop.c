#include "shell.h"

/**
 * main_shell_loop -> the main loop of the shell program
 *
 * @shell: a pointer to a struct shell
 * @argv: Argument Vector
 *
 * Return: 0 => Success, 1 => Failure
 */

int main_shell_loop(shell_t *shell, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		reset_shell(shell);
		if (interactive(shell))
			_puts("$ ");
		write_char(BUF_FLUSH);
		r = get_input(shell);
		if (r != -1)
		{
			init_shell(shell, argv);
			builtin_ret = get_built_in_command(shell);
			if (builtin_ret == -1)
				find_command(shell);
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

/**
 * reset_shell - reset the values of the shell struct for the next command.
 * @shell: struct address
 * Return: void
 */

void reset_shell(shell_t *shell)
{
	shell->arg = NULL;
	shell->argv = NULL;
	shell->path = NULL;
	shell->argc = 0;
}

/**
 * init_shell - initializes a `shell_t` struct
 * @shell: struct address
 * @argv: argument vector
 */

void init_shell(shell_t *shell, char **argv)
{
	int i = 0;

	shell->fname = argv[0];
	if (shell->arg)
	{
		shell->argv = str_to_words(shell->arg, " \t");
		if (!shell->argv)
		{

			shell->argv = malloc(sizeof(char *) * 2);
			if (shell->argv)
			{
				shell->argv[0] = _strdup(shell->arg);
				shell->argv[1] = NULL;
			}
		}
		for (i = 0; shell->argv && shell->argv[i]; i++)
			;
		shell->argc = i;

		replace_node_alias(shell);
		replace_shell_vars(shell);
	}
}
