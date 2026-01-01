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
