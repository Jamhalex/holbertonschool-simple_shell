#include "shell.h"

/**
 * strip_newline - removes trailing newline if present
 * @s: string to edit
 */

static void strip_newline(char *s)
{
	size_t i;

	if (s == NULL)
		return;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			return;
		}
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
 * run_shell - simple shell loop
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
	char *argv[64];
	int i;
	unsigned int line_count;
	line_count = 0;



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
			
		line_count++;

		/* tokenize into argv[] */
		i = 0;
		argv[i] = strtok(cmd, " \t");
		while (argv[i] != NULL && i < 63)
		{
			i++;
			argv[i] = strtok(NULL, " \t");
		}
		argv[i] = NULL;

		if (argv[0] == NULL)
			continue;

		if (execute_command(argv) == -1)
			print_not_found(av0, line_count, argv[0]);

	}
}

