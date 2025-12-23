#include "shell.h"

char *resolve_slash_cmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	if (access(cmd, F_OK) == 0)
		errno = EACCES;

	return (NULL);
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
