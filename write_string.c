#include "shell.h"

/**
 * write_string_char_by_char - prints an input string character by character
 * @str: A pointer to a character array (string) that needs to be printed
 *
 * Return: void
 */

void write_string_char_by_char(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_char(str[i]);
		i++;
	}
}

/**
 * write_char - writes characters to stderr in a buffer and
 * flushes the buffer when it
 * is full or when a flush signal is received.
 * @ch: The character to be written to the buffer
 *
 * Return: On success => 1.
 * On error => -1 is returned, and errno is set appropriately.
 */

int write_char(char ch)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == -1 || i >= WRITE_BUF_SIZE)
	{
		/* STDERR_FILENO => 2, which is a descriptor for standard error output. */
		write(STDERR_FILENO, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * write_char_to_buffer - writes characters to a buffer and
 * flushes it to a file descriptor when it reaches a
 * certain size or when a flush character is encountered.
 * @ch: The character to be written to the file descriptor or to the buffer
 * @fileDescriptor: The filedescriptor to write to
 *
 * Return: success => 1, error => -1, and errno is set appropriately.
 */

int write_char_to_buffer(char ch, int fileDescriptor)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fileDescriptor, buffer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * write_string_to_buffer - prints an input string
 * @str: the string to be printed
 * @fileDescriptor: the filedescriptor to write to
 *
 * Return: the number of characters written
 */

int write_string_to_buffer(char *str, int fileDescriptor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_char_to_buffer(*str++, fileDescriptor);
	}
	return (i);
}
