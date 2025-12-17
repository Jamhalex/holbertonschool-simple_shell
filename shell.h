#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "#cisfun$ "

int run_shell(char *av0);
int execute_command(char *cmd);

#endif /* SHELL_H */

