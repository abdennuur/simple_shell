#include "shell.h"

/**
 * the_builtins_list - search for a match and execute associate builtin
 * @data: struct for  program's data
 * Return: the return of the function executed if there is a match,
 * otherwise return -1.
 **/
int the_builtins_list(data_of_program *data)
{
	int itrtr;
	builtins options[] = {
		{"exit", the_builtin_exit},
		{"help", the_builtin_help},
		{"cd", the_builtin_cd},
		{"alias", the_builtin_alias},
		{"env", the_builtin_env},
		{"setenv", the_builtin_set_env},
		{"unsetenv", the_builtin_unset_env},
		{NULL, NULL}
	};

/* Walk through a structure*/
	for (itrtr = 0; options[itrtr].builtin != NULL; itrtr++)
	{
/*If there is a Match between the given comd and  builtin,*/
		if (str_compare(options[itrtr].builtin, data->command_name, 0))
		{
/*execute function, and return the return value of function*/
			return (options[itrtr].function(data));
		}
/*If no match return -1 */
	}
	return (-1);
}
