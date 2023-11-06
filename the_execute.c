#include "shell.h"
/**
 * the_execute - execute the command with entire path variables
 * @data: a ptr to program's data
 * Return: sucess returns 0 , otherwise return -1.
 */
int the_execute(data_of_program *data)
{
	int rtvl = 0, stts;
	pid_t pidd;

	/* check for the program in built ins */
	rtvl = the_builtins_list(data);
	if (rtvl != -1)/* if program was found in built ins */
		return (rtvl);

	/* check for a program file system */
	rtvl = the_find_program(data);
	if (rtvl)
	{/* if the program not found */
		return (rtvl);
	}
	else
	{/* if the program was found */
		pidd = fork(); /* create the child process */
		if (pidd == -1)
		{ /* if the fork call fail */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			rtvl = execve(data->tokens[0], data->tokens, data->env);
			if (rtvl == -1) /* if a error when exec*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am father, I wait and check the exit status of  child */
			wait(&stts);
			if (WIFEXITED(stts))
				errno = WEXITSTATUS(stts);
			else if (WIFSIGNALED(stts))
				errno = 128 + WTERMSIG(stts);
		}
	}
	return (0);
}
