#include "shell.h"

/**
 * the_print_alias - add or rm or show aliases
 * @data: struct for program's data
 * @alias: name of printed alias
 * Return: 0 -> sucess, or other nbr if its declared in the args
 */
int the_print_alias(data_of_program *data, char *alias)
{
	int ix, ji, alias_len;
	char buff[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_length(alias);
		for (ix = 0; data->alias_list[ix]; ix++)
		{
			if (!alias || (str_compare(data->alias_list[ix], alias, alias_len)
				&&	data->alias_list[ix][alias_len] == '='))
			{
				for (ji = 0; data->alias_list[ix][ji]; ji++)
				{
					buff[ji] = data->alias_list[ix][ji];
					if (data->alias_list[ix][ji] == '=')
						break;
				}
				buff[ji + 1] = '\0';
				buff_add(buff, "'");
				buff_add(buff, data->alias_list[ix] + ji + 1);
				buff_add(buff, "'\n");
				the_print(buff);
			}
		}
	}

	return (0);
}

/**
 * the_get_alias - add or rm or show aliases
 * @data: struct for program's data
 * @name: name of requested alias.
 * Return: 0 -> sucess, or other nbr if its declared in the args
 */
char *the_get_alias(data_of_program *data, char *name)
{
	int ix, alias_len;

	/* validate the args */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = str_length(name);

	for (ix = 0; data->alias_list[ix]; ix++)
	{/* Iterate through environ and check for coincidence of variable name */
		if (str_compare(name, data->alias_list[ix], alias_len) &&
			data->alias_list[ix][alias_len] == '=')
		{/* returns value of key NAME=  when find it */
			return (data->alias_list[ix] + alias_len + 1);
		}
	}
	/* returns -> NULL if its not find it */
	return (NULL);

}

/**
 * the_set_alias - add or override alias
 * @alias_string: seted  alias in the form (name='value')
 * @data: struct for program's data
 * Return: 0 -> sucess or other nbr if its declared in the args
 */
int the_set_alias(char *alias_string, data_of_program *data)
{
	int ix, ji;
	char buff[250] = {'0'}, *tmp = NULL;

	/* validate args */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterate alias to find = char */
	for (ix = 0; alias_string[ix]; ix++)
		if (alias_string[ix] != '=')
			buff[ix] = alias_string[ix];
		else
		{/* search ifvalue of the alias is another alias */
			tmp = the_get_alias(data, alias_string + ix + 1);
			break;
		}

	/* Iterates through alias list and check for coincidence of the variable name */
	for (ji = 0; data->alias_list[ji]; ji++)
		if (str_compare(buff, data->alias_list[ji], ix) &&
			data->alias_list[ji][ix] == '=')
		{/* if alias alredy exist */
			free(data->alias_list[ji]);
			break;
		}

	/* add  alias */
	if (tmp)
	{/* if alias already exist */
		buff_add(buff, "=");
		buff_add(buff, tmp);
		data->alias_list[ji] = str_duplicate(buff);
	}
	else /* if the alias does not exist */
		data->alias_list[ji] = str_duplicate(alias_string);
	return (0);
}
