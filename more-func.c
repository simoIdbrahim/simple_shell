#include "shell.h"

/**
 * interactive  - Checks if the shell is in interactive mode.
 * @info: Pointer to the info struct.
 *
 * Return: true if interactive mode, false otherwise.
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checked if a character is delim.
 * @h: The character to check.
 * @delim: delim str.
 *
 * Return: true || false.
 */

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha  - Checked for an alphabetic char.
 * @c: character to check.
 *
 * Return: check true || fasle.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts str to an int.
 * @s: convert the str.
 *
 * Return: false if no num in str, converted num otherwise.
 */

int _atoi(char *s)
{
	int idx, si = 1, warr = 0, outP;
	unsigned int res = 0;

	for (idx = 0; s[idx] != '\0' && warr != 2; idx++)
	{
		if (s[idx] == '-')
			si *= -1;

		if (s[idx] >= '0' && s[idx] <= '9')
		{
			warr = 1;
			res *= 10;
			res += (s[idx] - '0');
		}
		else if (warr == 1)
			warr = 2;
	}

	if (si == -1)
		outP = -res;
	else
		outP = res;

	return (outP);
}
