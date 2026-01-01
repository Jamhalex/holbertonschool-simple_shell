#include "shell.h"

/**
 * resolve_path - finds full path of a command using PATH
 * @cmd: command name
 * Return: malloc'd full path if found, or NULL
 */

char *resolve_path(char *cmd)
{
	char *path, *copy, *dir, *full;
	size_t len;

	if (!cmd || !*cmd)
		return (NULL);

	/* If cmd contains '/', treat as a direct path */
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	copy = strdup(path);
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

		strcpy(full, dir);
		strcat(full, "/");
		strcat(full, cmd);

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
