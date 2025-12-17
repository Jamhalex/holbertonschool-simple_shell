#include "shell.h"

extern char **environ;

/**
 * execute_command - forks and executes a command (single word, no args)
 * @cmd: command to execute (must be full path)
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *cmd)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
			exit(127);
	}

	if (wait(&status) == -1)
		return (-1);

	return (0);
}

