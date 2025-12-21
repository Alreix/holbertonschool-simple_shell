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

ssize_t read_command(char **line, size_t *buf_size, int interactive,
		unsigned long *line_number);
int handle_line(char *line, char **env, char *progname,
		unsigned long line_number, int interactive);

void clean_line(char *line);
int is_blank_line(char *line);
char **split_line(char *line, char *separator);
void free_tokens(char **tokens);

int fork_and_execute_cmd(char **argv, char **env, char *progname,
		unsigned long line_number, int interactive);

void print_not_found(char *progname, unsigned long line_number, char *cmd,
		int interactive);

#endif
