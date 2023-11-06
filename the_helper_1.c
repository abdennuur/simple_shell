#include "shell.h"

/**
 * the_free_recurrent_data - free fields needed ech loop
 * @data: struct of program's data
 * Return: no
 */
void the_free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		the_free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * the_free_all_data - free all field of  data
 * @data: struct of  program's data
 * Return: not
 */
void the_free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	the_free_recurrent_data(data);
	the_free_array_of_pointers(data->env);
	the_free_array_of_pointers(data->alias_list);
}

/**
 * the_free_array_of_pointers - free each ptr of array of ptrs and the
 * array
 * @array: array of ptrs
 * Return: no
 */
void the_free_array_of_pointers(char **array)
{
	int ix;

	if (array != NULL)
	{
		for (ix = 0; array[ix]; ix++)
			free(array[ix]);

		free(array);
		array = NULL;
	}
}
