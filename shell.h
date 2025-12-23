#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <string.h>

/* prompt.c*/
int print_prompt(void);

/* loop.c*/
ssize_t read_command(char **line, size_t *buf_size, int interactive,
		unsigned long *line_number);
int handle_line(char *line, char **env, char *progname,
		unsigned long line_number, int interactive);

/* parsing.c*/
void clean_line(char *line);
int is_blank_line(char *line);
char **split_line(char *line, char *separator);
void free_tokens(char **tokens);

/* execute.c*/
int fork_and_execute_cmd(char *path, char **argv, char **env);

/* error.c*/
void print_not_found(char *progname, unsigned long line_number,
		char *cmd, int interactive);
void print_permission_denied(char *progname, unsigned long line_number,
			     char *cmd, int interactive);

/* path.c*/
int exec_with_path(char **argv, char **env, char *progname,
		unsigned long line_number, int interactive);
int file_exists(char *path);
char *get_env_value(const char *name, char **env);
char *build_full_path(char *dir, char *cmd);
char *resolve_command(char *cmd, char **env);

/* path_util.c*/
char *resolve_slash_cmd(char *cmd);
char *search_in_path(char *cmd, char *path_value);

/* builtin.c*/
int exit_cmd(char **argv);
int env_cmd(char **argv);
void print_env(char **env);

#endif
