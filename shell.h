#ifndef SHELL_H
#define SHELL_H

/* ===== Standard headers (allowed) ===== */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

/* ===== Macros ===== */
#define PROMPT "($) "

/* ===== Structs ===== */
/**
 * struct shell_data - carries shell state across functions
 *
 * @av0: name used to invoke the shell (argv[0])
 * @line_count: number of lines processed (for error messages)
 * @env: environment variables
 */
typedef struct shell_data
{
	char *av0;
	unsigned int line_count;
	char **env;
} shell_data_t;

/* ===== Core loop ===== */
void shell_loop(shell_data_t *data);

/* ===== Input / parsing ===== */
char *read_line(int interactive);
char **tokenize_line(char *line);
void free_tokens(char **tokens);

char *find_command_path(char *cmd, char **env);

int execute_command(char **argv, shell_data_t *data);

int handle_builtin(char **argv, shell_data_t *data);

void print_error(shell_data_t *data, char *cmd);

int is_executable(char *path);

#endif /* SHELL_H */

