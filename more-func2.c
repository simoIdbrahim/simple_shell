#include "shell.h"

/**
 * _erratoi - Converts str to int
 * @s: covert the str
 *
 * Return: false if no num in str, converted num otherwise
 *       -1 on err
 */

int _erratoi(char *s)
{
	int ind = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (ind = 0; s[ind] != '\0'; ind++)
	{
		if (s[ind] >= '0' && s[ind] <= '9')
		{
			res *= 10;
			res += (s[ind] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - Print err mess
 * @info: Parameter and return info struct
 * @estr: str containing specified err type
 *
 * Return: None
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Function prints a decimal (integer) number (base 10)
 * @input: Input number
 * @fd: file descriptor to write
 *
 * Return: Num of char print.
 */

int print_d(int input, int fd)
{
	int (*custom_putchar)(char) = _putchar;
	int ind, coun = 0;
	unsigned int absolute_value, curr;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		custom_putchar('-');
		coun++;
	}
	else
		absolute_value = input;
	curr = absolute_value;
	for (ind = 1000000000; ind > 1; ind /= 10)
	{
		if (absolute_value / ind)
		{
			custom_putchar('0' + curr / ind);
			coun++;
		}
		curr %= ind;
	}
	custom_putchar('0' + curr);
	coun++;

	return (coun);
}

/**
 * convert_number - Converter fun, similar to itoa
 * @num: Number to be converted
 * @base: Base for conversion
 * @flags: Argument flags
 *
 * Return: str representation of the number
 */

char *convert_number(long int num, int base, int flags)
{
	static char *char_array;
	static char char_buffer[50];
	char si = 0;
	char *pointer;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		si = '-';
	}
	char_array = flags & CONVERT_LOWERCASE
		? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &char_buffer[49];
	*pointer = '\0';

	do {
		*--pointer = char_array[number % base];
		number /= base;
	} while (number != 0);

	if (si)
		*--pointer = si;
	return (pointer);
}

/**
 * remove_comments - Replaces first instance '#' with '\0'
 * @buf: Add of str to modify
 * Return: 0/fasle
 */

void remove_comments(char *buf)
{
	int ind;

	for (ind = 0; buf[ind] != '\0'; ind++)
	{
		if (buf[ind] == '#' && (!ind || buf[ind - 1] == ' '))
		{
			buf[ind] = '\0';
			break;
		}
	}
}
