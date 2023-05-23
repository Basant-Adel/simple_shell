#include "shell.h"

/**
 * is_command -> checks if a path is a command
 *
 * @shell: A pointer to a shell_t struct
 * @path: A string representing the path to a file or directory
 *
 * Return: 0 or 1
 */

int is_command(shell_t *shell, char *path)
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
 * find_command -> Finds a command in the path
 *
 * @shell:  a pointer to a struct representing the shell environment
 * Return: void
 */

void find_command(shell_t *shell)
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
		run_command(shell);
	}
	else
	{
		if ((interactive(shell) || get_env(shell, "PATH=")
			|| shell->argv[0][0] == '/') && is_command(shell, shell->argv[0]))
			run_command(shell);
		else if (*(shell->arg) != '\n')
		{
			shell->status = 127;
			print_error(shell, "not found\n");
		}
	}
}

/**
 * run_command -> runs a command by forking a child process and
 * executing the command using execve, and
 * then waits for the child process to finish and
 * updates the shell status accordingly.
 * @shell: a pointer to a struct containing info about the shell
 * and the command to be executed.
 * Return: void
 */

void run_command(shell_t *shell)
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
