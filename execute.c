#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * fork_and_execute_cmd - forks a child process and executes a command
 * @argv: argument vector (argv[0]is the command path)
 * @env: environment variables
 * @progname: name of the shell program for error messages
 * @line_number: input line number (non-interactive)
 * @interactive: 1 if interactive mode, 0 otherwise
 *
 * Return: 0 on success, -1 on failure
 */

int fork_and_execute_cmd(char **argv, char **env, char *progname,
		unsigned long line_number, int interactive)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (-1);
	}

	if (child == 0)
	{
		execve(argv[0], argv, env);

		if (errno == EACCES)
			exit(126);

		print_not_found(progname, line_number, argv[0], interactive);
		exit(127);
	}
	if (waitpid(child, &status, 0) == -1)
	{
		perror("waitpid");
		return (-1);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (0);
}
