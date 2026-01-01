#include "shell.h"

/**
 * build_full_path - builds full path from dir and cmd
 * @dir: directory from PATH
 * @cmd: command name
 *
 * Return: malloc'd full path, or NULL on failure
 */
static char *build_full_path(char *dir, char *cmd)
{
	char *full;
	size_t len;

	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);

	strcpy(full, dir);
	strcat(full, "/");
	strcat(full, cmd);

	return (full);
}

/**
 * search_in_path - search cmd in PATH string
 * @path: PATH value
 * @cmd: command name
 *
 * Return: malloc'd full path if found, otherwise NULL
 */
static char *search_in_path(char *path, char *cmd)
{
	char *copy, *dir, *full;

	copy = strdup(path);
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
		full = build_full_path(dir, cmd);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}

		free(full);
		dir = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}

/**
 * resolve_path - Resolve a command to a full executable path using PATH.
 * @cmd: Command name (e.g., "ls") or a path (e.g., "/bin/ls").
 *
 * Return: malloc'd string with resolved full path, otherwise NULL.
 */
char *resolve_path(char *cmd)
{
	char *path;

	if (!cmd || !*cmd)
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path || !*path)
		return (NULL);

	return (search_in_path(path, cmd));
}

