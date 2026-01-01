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

ssize_t read_command(char **line, size_t *buf_size, int interactive,
		int *line_number);
int handle_line(char *line, char **env, char *progname,
		int line_number);

void clean_line(char *line);
int is_blank_line(char *line);
char **split_line(char *line, char *separator);
void free_tokens(char **tokens);

int fork_and_execute_cmd(char **argv, char **env, char *progname,
		int line_number);

void print_not_found(char *progname, int line_number, char *cmd);
void print_permission_denied(char *progname, int line_count, char *cmd);
void no_such(char *progname, int line_count, char *cmd);

#endif
