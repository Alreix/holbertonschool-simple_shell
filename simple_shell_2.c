#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - entry point of the simple shell
 * @ac: argument count (unused)
 * @av: argument vector (used for program name in error messages)
 * @env: environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	char **argv = NULL;
	ssize_t read_line;
	size_t buffer_size = 0;
	int interactive = isatty(STDIN_FILENO);

	(void)ac;

	while (1)
	{
		if (interactive)
			print_prompt();

		read_line = getline(&line, &buffer_size, stdin);
		if (read_line == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		if (read_line > 0 && line[read_line - 1] == '\n')
			line[read_line - 1] = '\0';

		if (line[0] == '\0')
			continue;
		argv = split_line(line, " \t");
		if (argv == NULL)
			continue;

		if (argv[0] != NULL)
			fork_and_execute_command(argv, env, av[0]);

		free_tokens(argv);
		argv = NULL;
	}
	free(line);
	return (0);
}
