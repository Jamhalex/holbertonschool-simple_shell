#include "shell.h"

/**
 * run_shell - shell entry point
 * @av0: program name (argv[0])
 *
 * Return: 0 on exit (or status for "exit N")
 */
int run_shell(char *av0)
{
	return (shell_loop(av0));
}

