#include "shell.h"

/**
 * is_number - checks if a string is a non-negative number
 * @s: string
 * Return: 1 if number, 0 otherwise
 */
static int is_number(char *s)
{
	int i;

	if (!s || !*s)
		return (0);

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * handle_exit - handles the "exit" builtin
 * @argv: arguments array
 * @status: pointer to current status
 * Return: 1 if shell should exit, 0 otherwise
 */
int handle_exit(char **argv, int *status)
{
	int code;

	if (!argv || !argv[0] || strcmp(argv[0], "exit") != 0)
		return (0);

	if (argv[1])
	{
		if (!is_number(argv[1]))
		{
			*status = 2;
			return (1);
		}
		code = atoi(argv[1]);
		*status = code % 256;
	}
	return (1);
}

