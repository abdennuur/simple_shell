#include "shell.h"

/**
 * the_print - write a arr of chars in standar output
 * @string: ptr to array of chars
 * Return: the nbr of bytes writed or
 *  error -1 is returned, and errno set appropriately
 */
int the_print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * the_printe - write an arr of chars in standar error
 * @string: ptr to array of chars
 * Return: the nbr of bytes writed or
 * error -1 is returned and errno set appropriately
 */
int the_printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * the_print_error - write a arr of chars in standart error
 * @data: a ptr to program's data
 * @errorcode: ERroR code to Print
 * Return: the nbr of bytes writed or
 * error -1 is returned and errno set appropriately
 */
int the_print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	the_long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		the_printe(data->program_name);
		the_printe(": ");
		the_printe(n_as_string);
		the_printe(": ");
		the_printe(data->tokens[0]);
		if (errorcode == 2)
			the_printe(": Illegal number: ");
		else
			the_printe(": can't cd to ");
		the_printe(data->tokens[1]);
		the_printe("\n");
	}
	else if (errorcode == 127)
	{
		the_printe(data->program_name);
		the_printe(": ");
		the_printe(n_as_string);
		the_printe(": ");
		the_printe(data->command_name);
		the_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		the_printe(data->program_name);
		the_printe(": ");
		the_printe(n_as_string);
		the_printe(": ");
		the_printe(data->command_name);
		the_printe(": Permission denied\n");
	}
	return (0);
}
