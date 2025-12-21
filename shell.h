#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>


int print_prompt(void);

void clean_line(char *line);
int is_blank_line(char *line);

int fork_and_execute_cmd(char *cmd, char **env, char *progname,
		unsigned long line_number, int interactive);

void print_not_found(char *progname, unsigned long line_number, char *cmd,
		int interactive);


#endif
