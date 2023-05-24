#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @shell: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buffer(shell_t *shell, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, siginal);
#if USE_GETLINE
	r = getline(buf, &len_p, stdin);
#else
		r = get_line(shell, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			shell->linecount_flag = 1;
			rm_comments(*buf);
			build_history_list(shell, *buf, shell->histcount++);
			{
				*len = r;
				shell->cmd_buf = buf;
			}
		}
	} return (r);
}

/**
 * get_input - gets a line minus the newline
 * @shell: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(shell_t *shell)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(shell->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(shell, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(shell, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(shell, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			shell->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @shell: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(shell_t *shell, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(shell->fileDescriptor, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of input from STDIN
 * @shell: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int get_line(shell_t *shell, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(shell, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		str_cat_specific_char(new_p, buf + i, k - i);
	else
		str_cpy_specific_char(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * siginal - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void siginal(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
