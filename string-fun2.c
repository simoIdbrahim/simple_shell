#include "shell.h"

/**
 * _strcpy - the function handle copy str.
 * @dest: arg dest.
 * @src: arg src.
 *
 * Return: Pointer.
 */

char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}

	dest[index] = 0;
	return (dest);
}

/**
 * _strdup - copy the str.
 * @str: two string.
 *
 * Return: pointer two string.
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *result;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	for (len++; len--;)
		result[len] = *--str;
	return (result);
}

/**
 * _puts - print str.
 * @str: arg to print string.
 *
 * Return: void.
 */

void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - Writes char.
 * @c: print char.
 *
 * Return: if true return 1, if false 0.
 */

int _putchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
	{
		buffer[index] = c;
		index++;
	}

	return (1);
}
