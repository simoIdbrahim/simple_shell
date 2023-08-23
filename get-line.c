#include "shell.h"

/**
 * input_buf - Read input into a buffer and process it.
 * @information: Pointer to the info structure.
 * @buffer: Pointer to the input buffer.
 * @length: Pointer to the length of the input buffer.
 *
 * Return: Number of characters read.
 */

ssize_t input_buf(info_t *information, char **buffer, size_t *length)
{
	ssize_t read_count = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		read_count = getline(buffer, &length_p, stdin);
#else
		read_count = _getline(information, buffer, &length_p);
#endif

		if (read_count > 0)
		{
			if ((*buffer)[read_count - 1] == '\n')
			{
				(*buffer)[read_count - 1] = '\0';
				read_count--;
			}

			information->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(information,
					*buffer, information->histcount++);
			*length = read_count;
			information->cmd_buf = buffer;
		}
	}
	return (read_count);
}

/**
 * get_input - Get user input and handle it.
 * @information: Pointer to the info structure.
 *
 * Return: Number of characters read.
 */

ssize_t get_input(info_t *information)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t read_count = 0;
	char **buffer_p = &(information->arg), *p;

	_putchar(BUF_FLUSH);
	read_count = input_buf(information, &buffer, &length);

	if (read_count == -1)
		return (-1);

	if (length)
	{
		j = i;
		p = buffer + i;
		check_chain(information, buffer, &j, i, length);

		while (j < length)
		{
			if (is_chain(information, buffer, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= length)
		{
			i = length = 0;
			information->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p;
		return (_strlen(p));
	}

	*buffer_p = buffer;
	return (read_count);
}

/**
 * read_buffer - Read input buffer.
 * @information: Pointer to the info structure.
 * @buf: Buffer to read into.
 * @i: Pointer to the current index.
 *
 * Return: Number of characters read.
 */

ssize_t read_buffer(info_t *information, char *buf, size_t *i)
{
	ssize_t read_count = 0;

	if (*i)
		return (0);

	read_count = read(information->readfd, buf, READ_BUF_SIZE);

	if (read_count >= 0)
		*i = read_count;

	return (read_count);
}

/**
 * _getline - Read a line from input.
 * @information: Pointer to the info structure.
 * @ptr: Pointer to the buffer.
 * @length: Pointer to the length of the buffer.
 *
 * Return: Number of characters read.
 */

int _getline(info_t *information, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_count = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
		size = *length;

	if (i == len)
		i = len = 0;

	read_count = read_buffer(information, buf, &len);

	if (read_count == -1 || (read_count == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? (free(p), -1) : -1);

	if (size)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = size;

	*ptr = p;
	return (size);
}

/**
 * sigintHandler - Handle SIGINT (Ctrl+C) signal.
 * @sig_num: Signal number.
 */

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}
