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
 * run_shell - simple shell loop (no args, no PATH, no builtins)
 * @av0: program name (argv[0]) for error printing
 *
 * Return: 0 on exit
 */
int run_shell(char *av0)
{
	char *line;
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

		if (line[0] == '\0')
			continue;

		if (execute_command(line) == -1)
		{
			perror(av0);
		}
	}
}

