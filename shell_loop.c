#include "shell.h"

extern char **environ;

/**
 * strip_newline - removes trailing newline if present
 * @s: string to edit
 */
static void strip_newline(char *s)
{
	size_t i;

	if (s == NULL)
		return;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			return;
		}
		i++;
	}
}

/**
 * trim_spaces - trims leading and trailing spaces/tabs
 * @s: string to trim
 *
 * Return: pointer to first non-space char (inside s)
 */
static char *trim_spaces(char *s)
{
	size_t end;
	char *start;

	if (s == NULL)
		return (NULL);

	start = s;
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (start);

	end = strlen(start);
	while (end > 0 && (start[end - 1] == ' ' || start[end - 1] == '\t'))
	{
		start[end - 1] = '\0';
		end--;
	}

	return (start);
}

/**
 * run_shell - simple shell loop (no args, no PATH, no builtins)
 * @av0: program name (argv[0]) for error printing
 *
 * Return: 0 on exit
 */
int run_shell(char *av0)
{
	char *line, *cmd;
	size_t len;
	ssize_t nread;
	int interactive;

	line = NULL;
	len = 0;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			return (0);
		}

		strip_newline(line);
		cmd = trim_spaces(line);

		if (cmd[0] == '\0')
			continue;

		if (execute_command(cmd) == -1)
			perror(av0);
	}
}

