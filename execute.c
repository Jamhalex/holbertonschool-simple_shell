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
 * Return: exit status of child (0..255), or 127 on exec failure
 */
static int wait_child(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
		return (127);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (127);
}

/**
 * execute_command - Execute a command with arguments.
 * @argv: Null-terminated array of arguments.
 *
 * Return: exit status of command (0..255), or 127 if command not found.
 */
int execute_command(char **argv)
{
	pid_t pid;
	char *cmd_path;
	int rc;

	if (!argv || !argv[0])
		return (0);

	cmd_path = resolve_path(argv[0]);
	if (!cmd_path)
		return (127);

	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (127);
	}

	if (pid == 0)
		run_child(cmd_path, argv);

	free(cmd_path);
	rc = wait_child(pid);
	return (rc);
}

