#include "shell.h"

/**
 * expnd_variables - expand variables
 * @data: a pointer to struct of the program's data
 *
 * Return: nothing but sets errno.
 */
void expnd_variables(data_of_program *data)
{
	int ix, ji;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;
	buff_add(line, data->input_line);
	for (ix = 0; line[ix]; ix++)
		if (line[ix] == '#')
			line[ix--] = '\0';
		else if (line[ix] == '$' && line[ix + 1] == '?')
		{
			line[ix] = '\0';
			the_long_to_string(errno, expansion, 10);
			buff_add(line, expansion);
			buff_add(line, data->input_line + ix + 2);
		}
		else if (line[ix] == '$' && line[ix + 1] == '$')
		{
			line[ix] = '\0';
			the_long_to_string(getpid(), expansion, 10);
			buff_add(line, expansion);
			buff_add(line, data->input_line + ix + 2);
		}
		else if (line[ix] == '$' && (line[ix + 1] == ' ' || line[ix + 1] == '\0'))
			continue;
		else if (line[ix] == '$')
		{
			for (ji = 1; line[ix + ji] && line[ix + ji] != ' '; ji++)
				expansion[ji - 1] = line[ix + ji];
			tmp = the_env_get_key(expansion, data);
			line[ix] = '\0', expansion[0] = '\0';
			buff_add(expansion, line + ix + ji);
			tmp ? buff_add(line, tmp) : 1;
			buff_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expnd_alias - expans aliases
 * @data: a ptr to struct of the program's data
 *
 * Return: nothing but sets errno
 */
void expnd_alias(data_of_program *data)
{
	int ix, ji, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;

	buff_add(line, data->input_line);

	for (ix = 0; line[ix]; ix++)
	{
		for (ji = 0; line[ix + ji] && line[ix + ji] != ' '; ji++)
			expansion[ji] = line[ix + ji];
		expansion[ji] = '\0';

		tmp = the_get_alias(data, expansion);
		if (tmp)
		{
			expansion[0] = '\0';
			buff_add(expansion, line + ix + ji);
			line[ix] = '\0';
			buff_add(line, tmp);
			line[str_length(line)] = '\0';
			buff_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buff_add - append string at end of buffer
 * @buffer: Buffer to be filled
 * @str_to_add: str to be copied in buffer
 * Return: nothing but sets errno.
 */
int buff_add(char *buffer, char *str_to_add)
{
	int length, ix;

	length = str_length(buffer);
	for (ix = 0; str_to_add[ix]; ix++)
	{
		buffer[length + ix] = str_to_add[ix];
	}
	buffer[length + ix] = '\0';
	return (length + ix);
}
