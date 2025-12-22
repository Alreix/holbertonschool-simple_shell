#include "shell.h"
#include <string.h>

int exec_with_path(char **argv, char **env, char *progname,
		unsigned long line_number, int interactive)
{
	char *path;
	int status;

	path = resolve_command(argv[0], env);
	if (path == NULL)
	{
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
 * file_exists - checks if a file path exists on the filesystem
 * @path: path to the file
 *
 * Return: 1 if the file exists, 0 otherwise
 */
int file_exists(char *path)
{
	struct stat file_info;

	if (path == NULL)
		return (0);

	if (stat(path, &file_info) == 0)
		return (1);

	return (0);
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
 * build_full_path - build "dir/cmd"
 * @dir: directory
 * @cmd: command
 *
 * Return: malloc'd full path, or NULL
 */
char *build_full_path(char *dir, char *cmd)
{
	size_t len;
	char *full_path;

	if (dir == NULL || cmd == NULL)
		return (NULL);

	len = strlen(dir) + 1 + strlen(cmd) + 1;
	full_path = malloc(len);
	if (full_path == NULL)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
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
	char *path, *path_copy, *dir, *full_path;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (file_exists(cmd))
			return (strdup(cmd));
		return (NULL);
	}

	path = get_env_value("PATH", env);
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_full_path(dir, cmd);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

