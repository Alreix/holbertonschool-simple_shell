#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * fork_and_execute_cmd - forks and executes a command
 * @cmd: command path typed by user
 * @env: environment variables
 * @progname: argv[0] used for error messages
 * @line_count: input line number (non-interactive)
 *
 * Return: 0 on success, -1 on fork/wait failure
 */
int fork_and_execute_cmd(char *cmd, char **env, char *progname, int line_count)
{
	pid_t child;
	int status;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (-1);
	}
	if (child == 0)
	{
		execve(cmd, argv, env);
		if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		{
			print_permission_denied(progname, line_count, cmd);
			exit(126);
		}
			print_not_found(progname, line_count, cmd);
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
