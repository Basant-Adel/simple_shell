#include "shell.h"

/**
 * init_shell - initializes shell_t struct
 * @shell: struct address
 * @av: argument vector
 */

void init_shell(shell_t *shell, char **av)
{
	int i = 0;

	shell->fname = av[0];
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

		replace_alias(shell);
		replace_vars(shell);
	}
}