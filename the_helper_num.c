#include "shell.h"

/**
 * the_long_to_string - converts a nbr to a str
 * @number: number to be convert in an str
 * @string: buff to save the nbr as str
 * @base: base to convert nbr
 *
 * Return: no
 */
void the_long_to_string(long number, char *string, int base)
{
	int ix = 0, inNgtv = 0;
	long cocint = number;
	char ltrs[] = {"0123456789abcdef"};

	if (cocint == 0)
		string[ix++] = '0';

	if (string[0] == '-')
		inNgtv = 1;

	while (cocint)
	{
		if (cocint < 0)
			string[ix++] = ltrs[-(cocint % base)];
		else
			string[ix++] = ltrs[cocint % base];
		cocint /= base;
	}
	if (inNgtv)
		string[ix++] = '-';

	string[ix] = '\0';
	str_reverse(string);
}


/**
 * the_atoi - convert str to an int
 *
 * @s: ptr to str orig
 * Return: int of str or 0
 */
int the_atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - count the coincidences of character in string.
 *
 * @string: potr to str origen.
 * @character: strg with  chars to be counted
 * Return: int of str or 0
 */
int the_count_characters(char *string, char *character)
{
	int ix = 0, count = 0;

	for (; string[ix]; ix++)
	{
		if (string[ix] == character[0])
			count++;
	}
	return (count);
}
