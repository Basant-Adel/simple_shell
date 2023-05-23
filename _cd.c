#include "shell.h"

/**
 * _cd -> changes the current working directory of the shell
 *
 * @shell: A pointer to a struct representing
 * the shell environment and its variables
 *
 * Return: 0 or 1
 */

int _cd(shell_t *shell)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shell->argv[1])
	{
		dir = get_env(shell, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_env(shell, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(shell->argv[1], "-") == 0)
	{
		if (!get_env(shell, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(shell, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = get_env(shell, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(shell, "can't cd to ");
		write_string_char_by_char(shell->argv[1]), write_char('\n');
	}
	else
	{
		set_env(shell, "OLDPWD", get_env(shell, "PWD="));
		set_env(shell, "PWD", getcwd(buffer, 1024));
	} return (0);
}
