#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int print_prompt(void);

char **split_line(char *line, char *separator);
void free_tokens(char **tokens);

int fork_and_execute_command(char **argv, char **env, char *progname);

#endif
