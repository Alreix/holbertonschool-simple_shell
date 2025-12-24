#include "shell.h"
#include <string.h>

/**
 * exec_with_path - resolves command with PATH and executes it
 * @argv: command tokens
 * @env: environment
 * @progname: shell name
 * @line_number: current input line number
 * @interactive: interactive mode flag
 *
 * Return: command exit status, 126 on permission denied, 127 on not found,
 *         1 on internal error
 */
int exec_with_path(char **argv, char **env, char *progname,
		   unsigned long line_number, int interactive)
{
	char *path;
	int status;

	errno = 0;
	path = resolve_command(argv[0], env);
	if (path == NULL)
	{
		if (errno == EACCES)
		{
			print_permission_denied(progname, line_number,
						argv[0], interactive);
			return (126);
		}
		print_not_found(progname, line_number, argv[0], interactive);
		return (127);
	}

	status = fork_and_execute_cmd(path, argv, env);
	free(path);

	if (status == -1)
		return (1);

	return (status);
}

/**
 * get_env_value - get environment value for a given name
 * @name: variable name (example: "PATH")
 * @env: environment array
 *
 * Return: pointer to value inside env, or NULL
 */
char *get_env_value(const char *name, char **env)
{
	size_t len;
	int i;

	if (name == NULL || env == NULL)
		return (NULL);

	len = strlen(name);
	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (NULL);
}

/**
 * resolve_command - find executable path for a command using PATH
 * @cmd: command name (argv[0])
 * @env: environment
 *
 * Return: malloc'd full path if found, or NULL
 */
char *resolve_command(char *cmd, char **env)
{
	char *path_value;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/') != NULL)
		return (resolve_slash_cmd(cmd));

	path_value = get_env_value("PATH", env);
	if (path_value == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}

	return (search_in_path(cmd, path_value));
}
