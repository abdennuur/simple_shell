#include "shell.h"

/**
* the_getline - read line from the prmpt
* @data: struct for program data
*
* Return: read counting bytes
*/
int the_getline(data_of_program *data)
{
	char bf[BUFFER_SIZE] = {'\0'};
	static char *arr_commands[10] = {NULL};
	static char arr_operators[10] = {'\0'};
	ssize_t bytes_rd, ix = 0;

	/* check if does not exist more commands in array */
	/* and check the logical operators */
	if (!arr_commands[0] || (arr_operators[0] == '&' && errno != 0) ||
		(arr_operators[0] == '|' && errno == 0))
	{
		/*frees the memory allocated in array if exists */
		for (ix = 0; arr_commands[ix]; ix++)
		{
			free(arr_commands[ix]);
			arr_commands[ix] = NULL;
		}

		/* read from file descriptor int to bf */
		bytes_rd = read(data->file_descriptor, &bf, BUFFER_SIZE - 1);
		if (bytes_rd == 0)
			return (-1);

		/* split lines for \n or ; */
		ix = 0;
		do {
			arr_commands[ix] = str_duplicate(the_strtok(ix ? NULL : bf, "\n;"));
			/*check and split for && and || operators*/
			ix = the_check_lgc_ops(arr_commands, ix, arr_operators);
		} while (arr_commands[ix++]);
	}

	/*obtains the next command (cmd 0) and rm it for the array*/
	data->input_line = arr_commands[0];
	for (ix = 0; arr_commands[ix]; ix++)
	{
		arr_commands[ix] = arr_commands[ix + 1];
		arr_operators[ix] = arr_operators[ix + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - check and split for && nd || operators
* @arr_commands: array of commands
* @ix: index in array_commands to be checked
* @arr_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int the_check_lgc_ops(char *arr_commands[], int ix, char arr_operators[])
{
	char *tmp = NULL;
	int ji;

	/* check for & char in  command line*/
	for (ji = 0; arr_commands[ix] != NULL  && arr_commands[ix][ji]; ji++)
	{
		if (arr_commands[ix][ji] == '&' && arr_commands[ix][ji + 1] == '&')
		{
			/* split line whn chars && found */
			tmp = arr_commands[ix];
			arr_commands[ix][ji] = '\0';
			arr_commands[ix] = str_duplicate(arr_commands[ix]);
			arr_commands[ix + 1] = str_duplicate(tmp + ji + 2);
			ix++;
			arr_operators[ix] = '&';
			free(tmp);
			ji = 0;
		}
		if (arr_commands[ix][ji] == '|' && arr_commands[ix][ji + 1] == '|')
		{
			/* split line when chars || found */
			tmp = arr_commands[ix];
			arr_commands[ix][ji] = '\0';
			arr_commands[ix] = str_duplicate(arr_commands[ix]);
			arr_commands[ix + 1] = str_duplicate(tmp + ji + 2);
			ix++;
			arr_operators[ix] = '|';
			free(tmp);
			ji = 0;
		}
	}
	return (ix);
}
