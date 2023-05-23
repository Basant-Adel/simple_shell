#include "shell.h"

/**
 * is_cmd -> checks if a path is a command
 *
 * @shell: Parameter
 * @path: Parameter
 *
 * Return: Depend Condition
 */

int is_cmd(shell_t *shell, char *path)
{
	struct stat st;

	(void)shell;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_cmd -> Finds a command in the path
 *
 * @shell: Parameter
 */

void find_cmd(shell_t *shell)
{
	char *path = NULL;
	int i, k;

	shell->path = shell->argv[0];
	if (shell->linecount_flag == 1)
	{
		shell->line_count++;
		shell->linecount_flag = 0;
	}
	for (i = 0, k = 0; shell->arg[i]; i++)
		if (!is_delim(shell->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(shell, get_env(shell, "PATH="), shell->argv[0]);
	if (path)
	{
		shell->path = path;
		run_cmd(shell);
	}
	else
	{
		if ((interactive(shell) || get_env(shell, "PATH=")
			|| shell->argv[0][0] == '/') && is_cmd(shell, shell->argv[0]))
			run_cmd(shell);
		else if (*(shell->arg) != '\n')
		{
			shell->status = 127;
			print_error(shell, "not found\n");
		}
	}
}

/**
 * run_cmd -> Runs a command
 *
 * @shell: Parameter
 */

void run_cmd(shell_t *shell)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shell->path, shell->argv, get_environ(shell)) == -1)
		{
			free_shell(shell, 1);
			if (errno == EACCES)
				exit(PERMISSION_DENIED);
			exit(1);
		}
	}
	else
	{
		wait(&(shell->status));
		if (WIFEXITED(shell->status))
		{
			shell->status = WEXITSTATUS(shell->status);
			if (shell->status == PERMISSION_DENIED)
				print_error(shell, "Permission denied\n");
		}
	}
}
