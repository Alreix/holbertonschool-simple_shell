#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - entry point of the simple shell
 *
 * Description: This function implements a basic UNIX command line interpreter.
 * It displays a prompt in interactive mode, reads user input using getline,
 * executes commands using fork and execve, and handles end-of-file (Ctrl+D).
 *
 * @ac: argument count (unused)
 * @av: argument vector (used for program name in error messages)
 * @env: environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	ssize_t read_line;
	size_t buffer_size = 0;
	int line_count = 0;
	int interactive = isatty(STDIN_FILENO);
	int status = 0;

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
		line_count++;
		clean_line(line);

		if (is_blank_line(line))
			continue;

		status = fork_and_execute_cmd(line, env, av[0], line_number, interactive);
		if (status == -1)
			status = 1;
	}

	free(line);
	return (status);
}
