#include "shell.h"

extern char **environ;

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

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		_exit(127);
	}

	if (wait(&status) == -1)
		return (-1);

	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		return (-1);

	return (0);
}

