#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int print_prompt(void);
int fork_and_execute_command(char *cmd, char **env, char *progname);

#endif
