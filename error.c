#include "shell.h"

/**
 * print_not_found - prints a "not found" error message
 * @progname: program name (argv[0])
 * @line_number: input line number (non-interactive)
 * @cmd: command name that was not found
 */
void print_not_found(char *progname, unsigned long line_number, char *cmd)
{
	if (progname == NULL || cmd == NULL)
		return;

	if (cmd[0] == '\0')
		return;

	fprintf(stderr, "%s: %lu: %s: not found\n", progname,
			line_number, cmd);
}

/**
 * print_permission_denied - prints a permission denied error message
 * @progname: name of the shell program
 * @line_number: command line number (non-interactive)
 * @cmd: command that failed
 */
void print_permission_denied(char *progname, unsigned long line_number,
			     char *cmd)
{
	if (progname == NULL || cmd == NULL || cmd[0] == '\0')
		return;

	fprintf(stderr, "%s: %lu: %s: Permission denied\n", progname,
			line_number, cmd);
}
