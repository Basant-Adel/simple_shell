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
	/* `asm` is a keyword in C that allows inline assembly code to be written within a C program. In this
	specific code, `asm` is being used to move the value of the file descriptor `fileDescriptor` into the register
	`%0` and then add 3 to it. This is a way to modify the value of `fileDescriptor` using assembly language within
	the C program. */

	asm ("mov %1, %0\n\t"
	 	"add $3, %0" : "=r" (fileDescriptor) : "r" (fileDescriptor));

	if (argc == 2)
	{
		/* O_RDONLY => Open the file for reading only. */
		fileDescriptor = open(argv[1], O_RDONLY);

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
	shell_loop(shell, argv);
	return (EXIT_SUCCESS);
}
