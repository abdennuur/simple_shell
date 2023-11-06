#include "shell.h"

/**
 * the_builtin_env - show environment where shell runs
 * @data: struct for program's data
 * Return: 0 ->sucess, other nbr if its declared in the args
 */
int the_builtin_env(data_of_program *data)
{
	int ix;
	char cpyname[50] = {'\0'};
	char *var_cp = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		the_print_environ(data);
	else
	{
		for (ix = 0; data->tokens[1][ix]; ix++)
		{/* checks a char = */
			if (data->tokens[1][ix] == '=')
			{/* checks var with the same name and change value*/
			/* tmp */
				var_cp = str_duplicate(the_env_get_key(cpyname, data));
				if (var_cp != NULL)
					the_env_set_key(cpyname, data->tokens[1] + ix + 1, data);

				/* printenviron */
				the_print_environ(data);
				if (the_env_get_key(cpyname, data) == NULL)
				{/* print var if its not exist in environ */
					the_print(data->tokens[1]);
					the_print("\n");
				}
				else
				{/* returns the old value of the var*/
					the_env_set_key(cpyname, var_cp, data);
					free(var_cp);
				}
				return (0);
			}
			cpyname[ix] = data->tokens[1][ix];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * the_builtin_set_env - ..
 * @data: struct for program's data
 * Return: 0 -> sucess, or other nbr if its declared in the args
 */
int the_builtin_set_env(data_of_program *data)
{
	/* validate arguments */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	the_env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * the_builtin_unset_env - ..
 * @data: struct for program's data
 * Return: ..
 */
int the_builtin_unset_env(data_of_program *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	the_env_remove_key(data->tokens[1], data);

	return (0);
}
