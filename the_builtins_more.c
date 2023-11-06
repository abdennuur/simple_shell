#include "shell.h"

/**
 * the_builtin_exit - exit of program with status
 * @data: struct for program's data
 * Return: 0 ->sucess, or other number if its declared in the args
 */
int the_builtin_exit(data_of_program *data)
{
	int ix;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (ix = 0; data->tokens[1][ix]; ix++)
			if ((data->tokens[1][ix] < '0' || data->tokens[1][ix] > '9')
				&& data->tokens[1][ix] != '+')
			{/*if is not nbr*/
				errno = 2;
				return (2);
			}
		errno = the_atoi(data->tokens[1]);
	}
	the_free_all_data(data);
	exit(errno);
}

/**
 * the_builtin_cd - change current directory cd
 * @data: struct for program's data
 * Return: 0 -> sucess, or other nbr if its declared in the args
 */
int the_builtin_cd(data_of_program *data)
{
	char *dir_home = the_env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = the_env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = the_set_work_directory(data, dir_old);
			the_print(the_env_get_key("PWD", data));
			the_print("\n");

			return (error_code);
		}
		else
		{
			return (the_set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (the_set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int the_set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		the_env_set_key("PWD", new_dir, data);
	}
	the_env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * the_builtin_help - shows d environment where d shell runs
 * @data: struct forprogram's data
 * Return: 0 -> sucess, or other nbr if its declared in the args
 */
int the_builtin_help(data_of_program *data)
{
	int ix, len = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		the_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (ix = 0; mensajes[ix]; ix++)
	{
		len = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[ix], len))
		{
			the_print(mensajes[ix] + len + 1);
			return (1);
		}
	}
	/*if no match, print error and return -> -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * the_builtin_alias - add or remove or show aliases
 * @data: struct for program's data
 * Return: 0 -> sucess, or other nbr if its declared in the args
 */
int the_builtin_alias(data_of_program *data)
{
	int ix = 0;

	/* if no args, print all environment */
	if (data->tokens[1] == NULL)
		return (the_print_alias(data, NULL));

	while (data->tokens[++ix])
	{/* if args, set or print each env var*/
		if (the_count_characters(data->tokens[ix], "="))
			the_set_alias(data->tokens[ix], data);
		else
			the_print_alias(data, data->tokens[ix]);
	}

	return (0);
}
