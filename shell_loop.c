#include "shell.h"
#include <signal.h>
#include <string.h>
#include <unistd.h>

/**
 * sigint_handler - handles Ctrl+C signal in interactive mode
 * @sig: signal number
 */
static void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * run_shell - shell entry point
 * @av0: program name (argv[0])
 *
 * Return: 0 on exit (or status for "exit N")
 */
int run_shell(char *av0)
{
	if (isatty(STDIN_FILENO))
		signal(SIGINT, sigint_handler);

	return (shell_loop(av0));
}

