#include "shell.h"
/**
 * main - initialize vars of program
 * @argc: nbr of values received from command line
 * @argv: values received from command line
 * @env: number of values received from command line
 * Return: 0 --> succes
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL, NULL, NULL, 0, 0, NULL, NULL, NULL}, *data = &data_struct;
	char *prompt = "";

	the_inicialize_data(data, argc, argv, env);

	signal(SIGINT, the_handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	the_sisifo(prompt, data);
	return (0);
}

/**
 * the_handle_ctrl_c - print prompt in new line
 * when signal SIGINT ctrl + c is send to program
 * @UNUSED: prototype option
 */
void the_handle_ctrl_c(int opr UNUSED)
{
	the_print("\n");
	the_print(PROMPT_MSG);
}

/**
 * the_inicialize_data - inicialize struct with info of program
 * @data: ptr to structure of data
 * @argv: arr of args pased to program execution
 * @env: environ pased to program execution
 * @argc: nbr of values received from command line
 */
void the_inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int ix = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			the_printe(data->program_name);
			the_printe(": 0: Can't open ");
			the_printe(argv[1]);
			the_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[ix]; ix++)
		{
			data->env[ix] = str_duplicate(env[ix]);
		}
	}
	data->env[ix] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (ix = 0; ix < 20; ix++)
	{
		data->alias_list[ix] = NULL;
	}
}
/**
 * sisifo - infinite loop that show prompt
 * @prompt: printed prompt
 * @data: infinite loop that show the prompt
 */
void the_sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		the_print(prompt);
		error_code = string_len = the_getline(data);

		if (error_code == EOF)
		{
			the_free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expnd_alias(data);
			expnd_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = the_execute(data);
				if (error_code != 0)
					the_print_error(error_code, data);
			}
			the_free_recurrent_data(data);
		}
	}
}
