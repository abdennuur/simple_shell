#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* printf*/
#include <unistd.h> /* fork, execve*/
#include <stdlib.h>
#include <string.h> /* strtok*/
#include <stddef.h>
#include <errno.h> /* errno and perror */
#include <sys/types.h> /* type pid */
#include <sys/wait.h> /* wait */
#include <sys/stat.h> /* using stat function */
#include <signal.h> /* signal management */
#include <fcntl.h> /* open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for data program
 * @program_name: name of the executable
 * @input_line: ptr toinput read for _getline
 * @command_name: ptr to first command typed by user
 * @exec_counter: nbr of excecuted comands
 * @file_descriptor: file descriptor to input of commands
 * @tokens: ptr to array of tokenized input
 * @env: copy of environ
 * @alias_list: array of ptrs with aliases
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for builtins
 * @builtin: name of builtin
 * @function: associated function to be called for builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************* MAIN FUNCTIONS *************/


/*========  shell_main.c  ========*/

/* Inicializestruct with Info the program */
void the_inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Makes infinite loop to show the prompt*/
void the_sisifo(char *prompt, data_of_program *data);

/* Print the prompt in new line \n */
void the_handle_ctrl_c(int opr UNUSED);


/*========  the_getline.c  ========*/

/* Read one line of standar input*/
int the_getline(data_of_program *data);

/* split the each line for logical operators if it exist */
int the_check_lgc_ops(char *arr_commands[], int ix, char arr_operators[]);


/*======== the_expansions.c ========*/

/* expand variables */
void expnd_variables(data_of_program *data);

/* expand aliases */
void expnd_alias(data_of_program *data);

/* append the str to the end of the buffer*/
int buff_add(char *buffer, char *str_to_add);


/*======== the_str_tok.c ========*/

/* Separate str in tokens using designed delimiter */
void tokenize(data_of_program *data);

/* Creates ptr to  part of str */
char *the_strtok(char *line, char *delim);


/*======== the_execute.c ========*/

/* Execute a Command with its entire path */
int the_execute(data_of_program *data);


/*======== the_builtins_list.c ========*/

/* If match a builtin, executes it */
int the_builtins_list(data_of_program *data);


/*======== the_find_in_path.c ========*/

/* Creates an array of the path directories */
char **the_tokenize_path(data_of_program *data);

/* Search for program in path */
int the_find_program(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*======== the_helpers_free.c ========*/

/* Frees the memory for directories */
void the_free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void the_free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void the_free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*======== the_builtins_more.c ========*/

/* Close the shell */
int the_builtin_exit(data_of_program *data);

/* Change the current directory */
int the_builtin_cd(data_of_program *data);

/* set the work directory */
int the_set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int the_builtin_help(data_of_program *data);

/* set, unset and show alias */
int the_builtin_alias(data_of_program *data);


/*======== the_builtins_env.c ========*/

/* Shows the environment where the shell runs */
int the_builtin_env(data_of_program *data);

/* create or override a variable of environment */
int the_builtin_set_env(data_of_program *data);

/* delete a variable of environment */
int the_builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== the_env_management.c ========*/

/* Get value of environment var */
char *the_env_get_key(char *name, data_of_program *data);

/* Overwrite value of environment variabl */
int the_env_set_key(char *key, char *value, data_of_program *data);

/* Remove key from environment */
int the_env_remove_key(char *key, data_of_program *data);

/* print current environ */
void the_print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*======== the_helpers_print.c ========*/

/* Print a str in standar output */
int the_print(char *string);

/* Print a str in standar error */
int the_printe(char *string);

/* Prints a str in the standar error */
int the_print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== the_helpers_string.c ========*/

/* Count nbr of chars of str */
int str_length(char *string);

/* Dupl a str */
char *str_duplicate(char *string);

/* Comp 2 strs */
int str_compare(char *string1, char *string2, int number);

/* Concat 2 strs */
char *str_concat(char *string1, char *string2);

/* Reverse str */
void str_reverse(char *string);


/*======== the_helpers_numbers.c ========*/

/* Cast from int to string */
void the_long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int the_atoi(char *s);

/* count the coincidences of character in string */
int the_count_characters(char *string, char *character);


/*======== the_alias_management.c ========*/

/* print the list of alias */
int the_print_alias(data_of_program *data, char *alias);

/* get the alias name */
char *the_get_alias(data_of_program *data, char *alias);

/* set the alias name */
int the_set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */
