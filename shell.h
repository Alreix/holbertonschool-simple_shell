#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>


int print_prompt(void);

void clean_line(char *line);
int is_blank_line(char *line);

int fork_and_execute_cmd(char *cmd, char **env, char *progname,
		int line_count);

void print_not_found(char *progname, int line_count, char *cmd);
void print_permission_denied(char *progname, int line_count, char *cmd);
void no_such(char *progname, int line_count, char *cmd);

#endif
