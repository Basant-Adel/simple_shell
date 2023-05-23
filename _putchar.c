#include "shell.h"

/**
 * _putchar -> Writes the character c to stdout
 *
 * @c: The character to print
 *
 * Return: On success 1.
*/

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDOUT_FILENO, buf, i);
	/* STDOUT_FILENO => 1, which is a descriptor for standard output. */
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _puts -> Prints a string
 *
 * @str: Input
 */

void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
