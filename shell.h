#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define PROMPT "($)"

extern char **environ;

/* core */
int run_shell(char *av0);
int shell_loop(char *av0);
int execute_command(char **argv);

/* path */
char *resolve_path(char *cmd);

/* errors */
void print_not_found(char *av0, unsigned int line, char *cmd);

/* builtins */
int handle_exit(char **argv, int *status);
int handle_env(char **argv);
int run_builtins(char **argv, int *status);

/* loop helpers */
int read_command(char **line, size_t *len, char **cmd,
		int interactive, unsigned int *line_count);
int tokenize_args(char *cmd, char **argv, int max);
int run_external(char *av0, char **argv,
		unsigned int line_count);

/* utils */
void strip_newline(char *s);
char *trim_spaces(char *s);

#endif /* SHELL_H */

