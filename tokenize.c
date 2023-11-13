#include "shell.h"
/**
 * tokenize - function to separa str using designed delimiter
 * @data: a ptr to program data
 * Return: arr of different parts of str
 */
void tokenize(data_of_program *data)
{
	char *delmtr = " \t";
	int ix, ji, count = 2, len;

	len = str_length(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}

	for (ix = 0; data->input_line[ix]; ix++)
	{
		for (ji = 0; delmtr[ji]; ji++)
		{
			if (data->input_line[ix] == delmtr[ji])
				count++;
		}
	}

	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	ix = 0;
	data->tokens[ix] = str_duplicate(the_strtok(data->input_line, delmtr));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[ix++])
	{
		data->tokens[ix] = str_duplicate(the_strtok(NULL, delmtr));
	}
}
