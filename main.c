#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - entry point of the simple shell
 * @ac: argument count (unused)
 * @av: argument vector (used for program name)
 * @env: environment variables
 *
 * Return: last command exit status
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t buffer_size = 0;
	int interactive = isatty(STDIN_FILENO);
	unsigned long line_number = 0;
	int status = 0;

	(void)ac;

	while (1)
	{
		if (interactive)
			print_prompt();

		if (read_command(&line, &buffer_size, interactive, &line_number) == -1)
			break;

		status = handle_line(line, env, av[0], line_number, interactive);
	}

	free(line);
	return (status);
}
