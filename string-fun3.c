#include "shell.h"

/**
 * _strncpy - Copies a string
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 * @n: Maximum number of characters to copy
 *
 * Returns: Pointer to the copied string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int ind = 0, ind2;
	char *result = dest;

	while (src[ind] && ind < n - 1)
	{
		dest[ind] = src[ind];
		ind++;
	}
	if (ind < n)
	{
		ind2 = ind;
		while (ind2 < n)
		{
			dest[ind2] = '\0';
			ind2++;
		}
	}
	return (result);
}

/**
 * _strncat - the function Concatenates 2 str
 * @dest: Pointer to the first string
 * @src: Pointer to the second string
 * @n: Maximum number of bytes to use
 *
 * Returns: Pointer to the concatenated str
 */

char *_strncat(char *dest, char *src, int n)
{
	int ind1 = 0, ind2 = 0;
	char *result = dest;

	while (dest[ind1])
		ind1++;
	while (src[ind2] && ind2 < n)
	{
		dest[ind1] = src[ind2];
		ind1++;
		ind2++;
	}

	if (ind2 < n)
		dest[ind1] = '\0';
	return (result);
}

/**
 * _strchr - func char in str
 * @s: Pointer to the string to search
 * @c: The character to locate
 *
 * Returns: Pointer to the memory area containing the character in the string
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}
