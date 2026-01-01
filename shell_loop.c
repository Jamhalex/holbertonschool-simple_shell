#include "shell.h"

/**
 * tokenize - split a command string into argv array
 * @cmd: command string (modified in-place)
 * @argv: array to fill
 * @max: max number of args (including NULL)
 *
 * Return: 0 if argv[0] is NULL, 1 otherwise
 */
static int tokenize(char *cmd, char **argv, int max)
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
 * read_command - reads and prepares a command line
 * @line: buffer pointer for getline
 * @len: buffer size for getline
 * @cmd: pointer to trimmed command
 * @interactive: 1 if interactive mode
 * @line_count: command counter
 *
 * Return: 1 if a command is ready, 0 if empty line, -1 on EOF
 */
static int read_command(char **line, size_t *len, char **cmd,
			int interactive, unsigned int *line_count)
{
	ssize_t nread;

	if (interactive)
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

	nread = getline(line, len, stdin);
	if (nread == -1)
		return (-1);

	strip_newline(*line);
	*cmd = trim_spaces(*line);

	if ((*cmd)[0] == '\0')
		return (0);

	(*line_count)++;
	return (1);
}

/**
 * run_shell - simple shell loop
 * @av0: program name (argv[0]) for error printing
 *
 * Return: 0 on exit (or status for "exit N")
 */
int run_shell(char *av0)
{
	char *line, *cmd;
	size_t len;
	int interactive;
	char *argv[64];
	unsigned int line_count;
	int status;
	int rc;

	line = NULL;
	len = 0;
	interactive = isatty(STDIN_FILENO);
	line_count = 0;
	status = 0;

	while (1)
	{
		rc = read_command(&line, &len, &cmd, interactive, &line_count);
		if (rc == -1)
		{
			free(line);
			return (0);
		}
		if (rc == 0)
			continue;

		if (!tokenize(cmd, argv, 64))
			continue;

		if (handle_exit(argv, &status))
		{
			free(line);
			return (status);
		}

		if (execute_command(argv) == -1)
			print_not_found(av0, line_count, argv[0]);
	}

	return (0);
}

