#include "shell.h"

int the_check_file(char *full_path);

/**
 * the_find_program - finds program in path
 * @data: a pntr to program's data
 * Return: 0 success, errorcode Otherwise
 */

int the_find_program(data_of_program *data)
{
	int ix = 0, rt_code = 0;
	char **dir;

	if (!data->command_name)
		return (2);

	/**if full_path or executable in same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (the_check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dir = the_tokenize_path(data);/* search in PATH */

	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (ix = 0; dir[ix]; ix++)
	{/* appends function name to the path */
		dir[ix] = str_concat(dir[ix], data->tokens[0]);
		rt_code = the_check_file(dir[ix]);
		if (rt_code == 0 || rt_code == 126)
		{/* the the file ws found, is not a dir and execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dir[ix]);
			the_free_array_of_pointers(dir);
			return (rt_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	the_free_array_of_pointers(dir);
	return (rt_code);
}

/**
 * the_tokenize_path - tokenize path in dirs
 * @data: a ptr to program's data
 * Return: an array of path dirs
 */

char **the_tokenize_path(data_of_program *data)
{
	int ix = 0;
	int counter_dirs = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = the_env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*if path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the nbr of dirs in PATH */
	for (ix = 0; PATH[ix]; ix++)
	{
		if (PATH[ix] == ':')
			counter_dirs++;
	}

	/* reserve space for array of ptrs */
	tokens = malloc(sizeof(char *) * counter_dirs);

	/*tokenize and dup each token of path*/
	ix = 0;
	tokens[ix] = str_duplicate(the_strtok(PATH, ":"));
	while (tokens[ix++])
	{
		tokens[ix] = str_duplicate(the_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * the_check_file - check if exist a file, if it is not a dairectory and
 * if it has a excecution permisions for permisions
 * @full_path: ptr to full file name
 * Return: 0 success, or error code if exists
 */

int the_check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist file*/
	errno = 127;
	return (127);
}
