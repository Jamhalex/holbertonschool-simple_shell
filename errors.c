#include "shell.h"

/**
 * print_number - prints an unsigned integer using write
 * @n: number to print
 */
static void print_number(unsigned int n)
{
	char c;

	if (n >= 10)
		print_number(n / 10);

	c = (n % 10) + '0';
	write(STDERR_FILENO, &c, 1);
}

/**
 * print_not_found - prints "not found" error like /bin/sh
 * @av0: program name (argv[0])
 * @line: command counter (starts at 1)
 * @cmd: command name
 */
void print_not_found(char *av0, unsigned int line, char *cmd)
{
	if (!av0 || !cmd)
		return;

	write(STDERR_FILENO, av0, strlen(av0));
	write(STDERR_FILENO, ": ", 2);
	print_number(line);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}
