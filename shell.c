#include "shell.h"

/**
 * main -> Entry point
 *
 * @argc: Argument Count
 * @argv: Argument Vector
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/

int main(int argc, char **argv)
{
	shell_t shell[] = {shell_INIT};
	int fileDescriptor;

	fileDescriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0" : "=r" (fileDescriptor) : "r" (fileDescriptor));

	if (argc == 2) /* O_RDONLY => Open the file for reading only. */
	{
		fileDescriptor = open(argv[1], O_CREAT, S_IRUSR | S_IWUSR);

		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
			{
				write(STDERR_FILENO, "Permission denied\n", 18);
				exit(PERMISSION_DENIED);
			}
			if (errno == ENOENT)
			{
				printCanNotOpen(argv[0], argv[1]);
				exit(NOT_FOUND);
			}
			return (EXIT_FAILURE);
		}
		shell->fileDescriptor = fileDescriptor;
	}
	create_env_list(shell);
	read_history(shell);
	main_shell_loop(shell, argv);
	free_shell(shell, 1);
	return (EXIT_SUCCESS);
}
