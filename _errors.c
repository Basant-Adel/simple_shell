#include "shell.h"

/**
 * printCanNotOpen -> Prints an error indicating that a file can't be opened
 *  when a file cannot be opened.
 *
 * @programName: *char
 * @fileName: *char
 *
 * Return: void
 */

void printCanNotOpen(char *programName, char *fileName)
{
	write(STDERR_FILENO, programName, _strlen(programName));
	write(STDERR_FILENO, ": 0: Can't open ", 16);
	write(STDERR_FILENO, fileName, _strlen(fileName));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * print_error - prints an error message
 * @shell: the parameter & return shell struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

void print_error(shell_t *shell, char *estr)
{
	put_string(shell->fname);
	put_string(": ");
	print_base_10(shell->line_count, STDERR_FILENO);
	put_string(": ");
	put_string(shell->argv[0]);
	put_string(": ");
	put_string(estr);
}

/**
 * print_base_10 - function  that prints a decimal (integer) number (base 10)
 * to a specified file descriptor.
 * @input: the input
 * @fileDescriptor: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int print_base_10(int input, int fileDescriptor)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fileDescriptor == STDERR_FILENO)
		__putchar = put_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}