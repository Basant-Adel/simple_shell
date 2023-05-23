#include "shell.h"

/**
 * *_strdup -> Newly allocated space in memory
 *
 * @str: Input String
 *
 * Return: Depend Condition
 */

char *_strdup(const char *str)
{
	int i;
	int len;
	char *new;

	if (str == NULL)
		return (NULL);
	len = _strlen((char *)str);
	new = (char *) malloc(len + 1 * sizeof(char));
	if (new == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
	{
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}
