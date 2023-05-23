#include "shell.h"

/**
 * get_history -> It gets the history file
 * @shell: parameter struct
 * Return: allocated string containg history file
 */

char *get_history(shell_t *shell)
{
	char *buf, *dir;

	dir = get_env(shell, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * read_history -> Reads history file into a linked list
 *
 * @shell: Pointer
 *
 * Return: Depend Condition
 */

int read_history(shell_t *shell)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history(shell);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(shell, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(shell, buf + last, linecount++);
	free(buf);
	shell->histcount = linecount;
	while (shell->histcount-- >= HIST_MAX)
		delete_node(&(shell->history), 0);
	renumber_history(shell);
	return (shell->histcount);
}
