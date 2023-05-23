#include "shell.h"

/**
 * get_built_in_command -> Finds the built in command
 *
 * @shell: Parameter
 *
 * Return: Depend Condition
 */

int get_built_in_command(shell_t *shell)
{
	int i, built_in_found = -1;
	built_in_table _built_in_table[] = {
		{"exit", use_exit},
		{"env", print_env},
		{"help", _help},
		{"history", print_history},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; _built_in_table[i].type; i++)
		if (_strcmp(shell->argv[0], _built_in_table[i].type) == 0)
		{
			shell->line_count++;
			built_in_found = _built_in_table[i].func(shell);
			break;
		}
	return (built_in_found);
}