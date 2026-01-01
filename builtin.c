#include "shell.h"

/**
 * exit_cmd - Checks if argv is exactly "exit" with no arguments
 * @argv: tokenized command line
 *
 * Return: 1 if exit, 0 otherwise
 */
int exit_cmd(char **argv)
{
	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0 && argv[1] == NULL)
		return (1);

	return (0);
}

/**
 * env_cmd - Checks if argv is a builtin "env"
 * @argv: argument vector
 *
 * Return: 1 if is "env", 0 otherwise
 */
int env_cmd(char **argv)
{
	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "env") == 0 && argv[1] == NULL)
		return (1);

	return (0);
}

/**
 * print_env - prints the environnement variable
 * @env: environnement variables
 */
void print_env(char **env)
{
	int element = 0;

	if (env == NULL)
		return;

	while (env[element] != NULL)
	{
		printf("%s\n", env[element]);
		element++;
	}
}
