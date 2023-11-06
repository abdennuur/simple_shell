#include "shell.h"
/**
 * the_strtok - separate strs with delimiters
 * @line: It´s ptr to array we receive in getline
 * @delim:  characters we mark off str in parts
 * Return: ptr to created token
*/
char *the_strtok(char *line, char *delim)
{
	int ji;
	static char *tstr;
	char *cpstr;

	if (line != NULL)
		tstr = line;
	for (; *tstr != '\0'; tstr++)
	{
		for (ji = 0; delim[ji] != '\0'; ji++)
		{
			if (*tstr == delim[ji])
			break;
		}
		if (delim[ji] == '\0')
			break;
	}
	cpstr = tstr;
	if (*cpstr == '\0')
		return (NULL);
	for (; *tstr != '\0'; tstr++)
	{
		for (ji = 0; delim[ji] != '\0'; ji++)
		{
			if (*tstr == delim[ji])
			{
				*tstr = '\0';
				tstr++;
				return (cpstr);
			}
		}
	}
	return (cpstr);
}
