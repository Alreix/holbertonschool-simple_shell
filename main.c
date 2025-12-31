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
 * Return: last command exit status
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t buffer_size = 0;
	int interactive = isatty(STDIN_FILENO);
	int line_number = 0;
	int status = 0;

	(void)ac;

	while (1)
	{
		if (interactive)
			print_prompt();

		if (read_command(&line, &buffer_size, interactive, &line_number) == -1)
			break;

		status = handle_line(line, env, av[0], line_number);
	}

	free(line);
	return (status);
}
