#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * fork_and_execute_cmd - forks and executes a command
 * @argv: command path typed by user
 * @env: environment variables
 * @progname: argv[0] used for error messages
 * @line_number: input line number (non-interactive)
 *
 * Return: 0 on success, -1 on fork/wait failure
 */
int fork_and_execute_cmd(char **argv, char **env, char *progname,
		int line_number)
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
		{
			print_permission_denied(progname, line_number, argv[0]);
			exit(126);
		}
		else
		{
			print_not_found(progname, line_number, argv[0]);
			exit(127);
		}
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
