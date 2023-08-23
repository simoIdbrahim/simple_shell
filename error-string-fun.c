#include "shell.h"

/**
 * _eputs - Print a string to standard error.
 * @str: str printed.
 * Return: None.
 */

void _eputs(char *str)
{
	if (!str)
	{
		return;
	}

	for (int i = 0; str[i] != '\0'; i++)
	{
		_eputchar(str[i]);
	}
}

/**
 * _eputchar - Writes a character to standard error.
 * @c: char to print.
 * Return: On success, true.
 *         On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
	{
		buffer[index++] = c;
	}

	return (1);
}

/**
 * _putfd - Writes a character to the given file descriptor.
 * @c: arg char to print.
 * @fd: arg file descriptor to write.
 * Return: On success, true.
 *         On error, false is returned.
 */

int _putfd(char c, int fd)
{
	static int ind;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ind >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, ind);
		ind = 0;
	}

	if (c != BUF_FLUSH)
	{
		buffer[ind++] = c;
	}

	return (1);
}

/**
 * _putsfd - Prints a str to the given file descriptor.
 * @str: arg str to be printed.
 * @fd: arg file descriptor to write.
 * Return:  num of chars to put.
 */

int _putsfd(char *str, int fd)
{
	if (!str)
	{
		return (0);
	}

	int count = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		count += _putfd(str[i], fd);
	}

	return (count);
}
