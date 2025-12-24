#include "shell.h"

char *resolve_slash_cmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	if (access(cmd, F_OK) == 0)
		errno = EACCES;

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

char *search_in_path(char *cmd, char *path_value)
{
	char *path_copy, *dir, *full_path;

	path_copy = strdup(path_value);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_full_path(dir, cmd);
		if (full_path == NULL)
			break;

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		if (access(full_path, F_OK) == 0)
		{
			free(full_path);
			free(path_copy);
			errno = EACCES;
			return (NULL);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
