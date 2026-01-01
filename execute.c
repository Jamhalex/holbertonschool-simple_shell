#include "shell.h"
#include <sys/wait.h>

/**
 * run_child - execute command in child process
 * @cmd_path: resolved executable path
 * @argv: argument vector
 */
static void run_child(char *cmd_path, char **argv)
{
	execve(cmd_path, argv, environ);
	free(cmd_path);
	_exit(127);
}

/**
 * wait_child - wait for child process to finish
 * @pid: child pid
 *
 * Return: 0 on success, -1 on failure
 */
static int wait_child(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
		return (-1);

	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		return (-1);

	return (0);
}

/**
 * execute_command - Execute a command with arguments.
 * @argv: Null-terminated array of arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char **argv)
{
	pid_t pid;
	char *cmd_path;

	if (!argv || !argv[0])
		return (0);

	cmd_path = resolve_path(argv[0]);
	if (!cmd_path)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (-1);
	}

	if (pid == 0)
		run_child(cmd_path, argv);

	free(cmd_path);
	return (wait_child(pid));
}

