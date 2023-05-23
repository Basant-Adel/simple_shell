#include "shell.h"

/**
 * printCanNotOpen -> Prints an error message to standard error
 *  when a file cannot be opened.
 *
 * @programName: char
 * @fileName: char
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