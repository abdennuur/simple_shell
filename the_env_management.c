#include "shell.h"

/**
 * the_env_get_key - get value of environment var
 * @key:environment var of interest
 * @data: struct of program's data
 * Return: a ptr to value of var or NULL if its not exist
 */
char *the_env_get_key(char *key, data_of_program *data)
{
	int ix, key_len = 0;

	/* validate args */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains len of variable requested */
	key_len = str_length(key);

	for (ix = 0; data->env[ix]; ix++)
	{/* Iterates through environ and check for coincidence of vame */
		if (str_compare(key, data->env[ix], key_len) &&
		 data->env[ix][key_len] == '=')
		{/* return value of key NAME=  when find it*/
			return (data->env[ix] + key_len + 1);
		}
	}
	/* return NULL if not find it */
	return (NULL);
}

/**
 * the_env_set_key - overwrite value of environment var
 * or create it if its not exist.
 * @key: name of var to set
 * @value: New Value
 * @data: struct of program's data
 * Return: 1 -> parameters are NULL, 2 -> error or 0 -> sucess.
 */

int the_env_set_key(char *key, char *value, data_of_program *data)
{
	int ix, key_len = 0, the_new_key = 1;

	/* validate args */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains len of var requested */
	key_len = str_length(key);

	for (ix = 0; data->env[ix]; ix++)
	{/* Iterate through environ and check for coincidence of vame */
		if (str_compare(key, data->env[ix], key_len) &&
		 data->env[ix][key_len] == '=')
		{/* If key exists */
			the_new_key = 0;
			/* free entire var, its new created below */
			free(data->env[ix]);
			break;
		}
	}
	/* make str of form key=value */
	data->env[ix] = str_concat(str_duplicate(key), "=");
	data->env[ix] = str_concat(data->env[ix], value);

	if (the_new_key)
	{/* if var is new, its created in end of the actual list and we need*/
	/* to put NULL value in  next position */
		data->env[ix + 1] = NULL;
	}
	return (0);
}

/**
 * the_env_remove_key - rm key from environment
 * @key: key 2 remove
 * @data: sructure of program's data
 * Return: 1 -> key was removed, 0 -> key not exist;
 */
int the_env_remove_key(char *key, data_of_program *data)
{
	int ix, key_len = 0;

	/* validate args */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains len of var requested */
	key_len = str_length(key);

	for (ix = 0; data->env[ix]; ix++)
	{/* iterate through environ and check for coincidences */
		if (str_compare(key, data->env[ix], key_len) &&
		 data->env[ix][key_len] == '=')
		{/* if the key already exist, rm them */
			free(data->env[ix]);

			/* move other keys one position down */
			ix++;
			for (; data->env[ix]; ix++)
			{
				data->env[ix - 1] = data->env[ix];
			}
			/* put NULL value in the new end of list */
			data->env[ix - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * the_print_environ - print current environ
 * @data: struct 4 program's data
 * Return: none
 */
void the_print_environ(data_of_program *data)
{
	int ji;

	for (ji = 0; data->env[ji]; ji++)
	{
		the_print(data->env[ji]);
		the_print("\n");
	}
}
