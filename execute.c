#include "shell.h"

extern char **environ;

/**
 * has_slash - checks if command contains a '/'
 * @s: string to check
 *
 * Return: 1 if found, 0 otherwise
 */
static int has_slash(const char *s)
{
	if (s == NULL)
		return (0);

	for (; *s; s++)
	{
		if (*s == '/')
			return (1);
	}

	return (0);
}

/**
 * build_path - builds full path from dir and command
 * @dir: directory from PATH (can be empty)
 * @cmd: command name
 *
 * Return: newly allocated full path, or NULL on failure
 */
static char *build_path(const char *dir, const char *cmd)
{
	size_t dlen, clen;
	int need_sep;
	char *full;

	dlen = strlen(dir);
	clen = strlen(cmd);
	need_sep = (dlen > 0 && dir[dlen - 1] != '/');

	full = malloc(dlen + need_sep + clen + 1);
	if (full == NULL)
		return (NULL);

	memcpy(full, dir, dlen);
	if (need_sep)
		full[dlen++] = '/';
	memcpy(full + dlen, cmd, clen);
	full[dlen + clen] = '\0';

	return (full);
}

/**
 * resolve_command - resolves command using PATH when needed
 * @cmd: command to resolve
 *
 * Return: newly allocated full path, or NULL if not found
 */
static char *resolve_command(const char *cmd)
{
	char *path_env, *path_copy, *token, *full;

	if (cmd == NULL || *cmd == '\0')
		return (NULL);

	if (has_slash(cmd))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		errno = ENOENT;
		return (NULL);
	}

	path_env = getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
	{
		errno = ENOENT;
		return (NULL);
	}

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full = build_path(token, cmd);
		if (full == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		if (access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	errno = ENOENT;
	return (NULL);
}

/**
 * execute_command - forks and executes a command with arguments
 * @argv: NULL-terminated argument vector
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **argv)
{
	pid_t pid;
	int status;
	char *resolved;

	resolved = resolve_command(argv[0]);
	if (resolved == NULL)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		free(resolved);
		return (-1);
	}

	if (pid == 0)
	{
		execve(resolved, argv, environ);
		_exit(127);
	}

	if (wait(&status) == -1)
	{
		free(resolved);
		return (-1);
	}

	free(resolved);

	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		return (-1);

	return (0);
}

