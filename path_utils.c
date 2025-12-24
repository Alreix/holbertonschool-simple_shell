#include "shell.h"

/**
 * resolve_slash_cmd - resolves a command containing '/'.
 * @cmd: command path to check
 *
 * Return: malloc'd copy of cmd if executable, or NULL on failure.
 * If cmd exists but is not executable, sets errno to EACCES.
 */
char *resolve_slash_cmd(char *cmd)
{
	struct stat st;

	if (cmd == NULL || cmd[0] == '\0')
	{
		errno = ENOENT;
		return (NULL);
	}

	if (stat(cmd, &st) == -1)
		return (NULL);

	if (S_ISDIR(st.st_mode))
	{
		errno = EACCES;
		return (NULL);
	}

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

/**
 * search_in_path - searches PATH directories for an executable command.
 * @cmd: command name to find
 * @path_value: PATH value (colon-separated directories)
 *
 * Return: malloc'd full path if found and executable, or NULL.
 * If at least one match exists but is not executable, sets errno to EACCES.
 */
char *search_in_path(char *cmd, char *path_value)
{
	char *path_copy, *dir, *full_path;
	int perm_denied = 0;

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
			perm_denied = 1;

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);

	if (perm_denied)
		errno = EACCES;

	return (NULL);
}
