#include "shell.h"

/**
 * *str_cpy_specific_char -> Copy a specified number of
 *characters from a source string into a destination string
 *
 *@dest: Empty Input
 *@src: Input Source
 *@n: Input Number
 *
 *Return: Destinse String
 */

char *str_cpy_specific_char(char *dest, char *src, int n)
{
	int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * *str_cat_specific_char -> Appends specified number of characters from
 * 'src' string to the end of the 'dest' string
 *
 * @dest: Destination Input
 * @src: Source Input
 * @n: Number Elements
 *
 * Return: Destination
 */

char *str_cat_specific_char(char *dest, char *src, int n)
{
	int i;
	int j;

	i = _strlen(dest);
	for (j = 0; dest[j] != '\0' && j < n; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
