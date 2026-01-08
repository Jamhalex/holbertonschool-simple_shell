#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/**
 * handle_cd - builtin: cd [dir]
 * @argv: argument vector
 * @status: pointer to shell status
 *
 * Return: 1 if handled, 0 otherwise
 */
int handle_cd(char **argv, int *status)
{
	char *dest;

	if (!argv || !argv[0] || strcmp(argv[0], "cd") != 0)
		return (0);

	dest = argv[1];

	/* cd with no argument -> HOME */
	if (!dest || dest[0] == '\0')
		dest = getenv("HOME");

	if (!dest)
		dest = "/";

	if (chdir(dest) != 0)
	{
		perror("cd");
		*status = 2;
	}
	else
	{
		*status = 0;
	}

	return (1);
}

/**
 * handle_setenv - builtin: setenv KEY VALUE
 * @argv: argument vector
 * @status: pointer to shell status
 *
 * Return: 1 if handled, 0 otherwise
 */
int handle_setenv(char **argv, int *status)
{
	if (!argv || !argv[0] || strcmp(argv[0], "setenv") != 0)
		return (0);

	if (!argv[1] || !argv[2])
	{
		fprintf(stderr, "setenv: usage: setenv KEY VALUE\n");
		*status = 2;
		return (1);
	}

	if (setenv(argv[1], argv[2], 1) != 0)
	{
		perror("setenv");
		*status = 2;
	}
	else
	{
		*status = 0;
	}

	return (1);
}

/**
 * handle_unsetenv - builtin: unsetenv KEY
 * @argv: argument vector
 * @status: pointer to shell status
 *
 * Return: 1 if handled, 0 otherwise
 */
int handle_unsetenv(char **argv, int *status)
{
	if (!argv || !argv[0] || strcmp(argv[0], "unsetenv") != 0)
		return (0);

	if (!argv[1])
	{
		fprintf(stderr, "unsetenv: usage: unsetenv KEY\n");
		*status = 2;
		return (1);
	}

	if (unsetenv(argv[1]) != 0)
	{
		perror("unsetenv");
		*status = 2;
	}
	else
	{
		*status = 0;
	}

	return (1);
}

