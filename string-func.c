#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: The string to calculate the length of.
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*(s++))
		length++;

	return (length);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, 0 if s1 == s2.
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a specific substring.
 * @haystack: The string to search within.
 * @needle: The substring to search for.
 *
 * Return: Address of the next character after the match in haystack, or NULL.
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * _strcat - stick two strings.
 * @dest: arg one.
 * @src: arge two.
 *
 * Return: Pointer.
 */

char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
		*(dest++) = *(src++);
	*dest = *src;
	return (result);
}
