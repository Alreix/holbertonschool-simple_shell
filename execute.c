#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/**
 * fork_and_execute_cmd - forks a child process and executes a command
 * @path: resolved executable path
 * @argv: argument vector (argv[0]is the command path)
 * @env: environment variables
 *
 * Return: exit status, or -1 on fork/wait error
 */

int fork_and_execute_cmd(char *path, char **argv, char **env)
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
		execve(path, argv, env);
		if (errno == EACCES)
			exit(126);
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
