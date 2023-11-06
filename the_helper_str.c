#include "shell.h"

/**
 * str_length - return the len of a str
 * @string: ptr to str
 * Return: lent of str
 */
int str_length(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_duplicate - duplicates a str
 * @string: str to be cp
 * Return: ptr to arr
 */
char *str_duplicate(char *string)
{
	char *rslt;
	int len, ix;

	if (string == NULL)
		return (NULL);

	len = str_length(string) + 1;

	rslt = malloc(sizeof(char) * len);

	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (ix = 0; ix < len ; ix++)
	{
		rslt[ix] = string[ix];
	}

	return (rslt);
}

/**
 * str_compare - cpr 2 strs
 * @string1: Str 1, or shorter
 * @string2: Str 2, or longer
 * @number: nbr of chars to be compared, -> 0 if infinite
 * Return: -> 1 if strs are equals , ->0 if the strs different
 */
int str_compare(char *string1, char *string2, int number)
{
	int itrtr;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* Infinit Longitud */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (itrtr = 0; string1[itrtr]; itrtr++)
		{
			if (string1[itrtr] != string2[itrtr])
				return (0);
		}
		return (1);
	}
	else /* if is a nbr of chars to be compare */
	{
		for (itrtr = 0; itrtr < number ; itrtr++)
		{
			if (string1[itrtr] != string2[itrtr])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concat 2 strs
 * @string1: Str to be concatenated
 * @string2: Str to be concatenated
 *
 * Return: ptr to arr
 */
char *str_concat(char *string1, char *string2)
{
	char *rslt;
	int len1 = 0, len2 = 0;

	if (string1 == NULL)
		string1 = "";
	len1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	len2 = str_length(string2);

	rslt = malloc(sizeof(char) * (len1 + len2 + 1));
	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* cp of str1 */
	for (len1 = 0; string1[len1] != '\0'; len1++)
		rslt[len1] = string1[len1];
	free(string1);

	/* cp of str2 */
	for (len2 = 0; string2[len2] != '\0'; len2++)
	{
		rslt[len1] = string2[len2];
		len1++;
	}

	rslt[len1] = '\0';
	return (rslt);
}


/**
 * str_reverse - reverses a str
 *
 * @string: potr to str
 * Return: (void)
 */
void str_reverse(char *string)
{

	int ix = 0, len = str_length(string) - 1;
	char hold;

	while (ix < len)
	{
		hold = string[ix];
		string[ix++] = string[len];
		string[len--] = hold;
	}
}
