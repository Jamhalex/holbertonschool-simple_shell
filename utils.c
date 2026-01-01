#include "shell.h"

/**
 * strip_newline - removes trailing newline if present
 * @s: string to edit
 */
void strip_newline(char *s)
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
char *trim_spaces(char *s)
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
 * tokenize_args - split a command string into argv array
 * @cmd: command string (modified in-place)
 * @argv: array to fill
 * @max: max number of args (including NULL)
 *
 * Return: 0 if argv[0] is NULL, 1 otherwise
 */
int tokenize_args(char *cmd, char **argv, int max)
{
	int i;

	i = 0;
	argv[i] = strtok(cmd, " \t");
	while (argv[i] != NULL && i < (max - 1))
	{
		i++;
		argv[i] = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	if (argv[0] == NULL)
		return (0);

	return (1);
}
/**
 * run_external - run non-builtin commands and report not found
 * @av0: program name (argv[0])
 * @argv: argument vector
 * @line_count: command counter
 */
void run_external(char *av0, char **argv, unsigned int line_count)
{
	if (execute_command(argv) == -1)
		print_not_found(av0, line_count, argv[0]);
}

