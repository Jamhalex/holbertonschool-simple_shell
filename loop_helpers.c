#include "shell.h"

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
int read_command(char **line, size_t *len, char **cmd,
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
 * run_builtins - handle builtins for current argv
 * @argv: argument vector
 * @status: status for exit builtin
 *
 * Return: 1 if should continue loop, -1 if should exit, 0 otherwise
 */
int run_builtins(char **argv, int *status)
{
	if (handle_exit(argv, status))
		return (-1);

	if (handle_env(argv))
		return (1);

	return (0);
}

/**
 * handle_line - process a single command line
 * @av0: program name
 * @cmd: trimmed command string
 * @line_count: command counter
 * @status: status for exit builtin
 *
 * Return: 1 to continue, -1 to exit
 */
static int handle_line(char *av0, char *cmd, unsigned int line_count,
		int *status)

{
	char *argv[64];
	int rc;

	if (!tokenize_args(cmd, argv, 64))
		return (1);

	rc = run_builtins(argv, status);
	if (rc == -1)
		return (-1);

	if (rc == 1)
		return (1);

	run_external(av0, argv, line_count);
	return (1);
}

/**
 * shell_loop - runs the main shell loop
 * @av0: program name (argv[0]) for error printing
 *
 * Return: 0 on exit (or status for "exit N")
 */
int shell_loop(char *av0)
{
	char *line, *cmd;
	size_t len;
	int interactive;
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

		if (handle_line(av0, cmd, line_count, &status) == -1)
		{
			free(line);
			return (status);
		}
	}
}

