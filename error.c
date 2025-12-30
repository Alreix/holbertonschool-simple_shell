#include "shell.h"

/**
 * print_not_found - prints a "not found" error message
 * @progname: program name (argv[0])
 * @line_number: input line number (non-interactive)
 * @cmd: command name that was not found
 * @interactive: if the shell is in interactive mode
 */
void print_not_found(char *progname, unsigned long line_number,
		char *cmd, int interactive)
{
	if (progname == NULL || cmd == NULL)
		return;

	if (cmd[0] == '\0')
		return;

	if (interactive)
		fprintf(stderr, "%s: %s: not found\n", progname, cmd);
	else
		fprintf(stderr, "%s: %lu: %s: not found\n", progname,
			line_number, cmd);
}

/**
 * print_permission_denied - prints a permission denied error message
 * @progname: name of the shell program
 * @line_number: command line number (non-interactive)
 * @cmd: command that failed
 * @interactive: if the shell is in interactive mode
 */
void print_permission_denied(char *progname, unsigned long line_number,
			     char *cmd, int interactive)
{
	if (progname == NULL || cmd == NULL || cmd[0] == '\0')
		return;

	if (interactive)
		fprintf(stderr, "%s: %s: permission denied\n", progname, cmd);

	else
		fprintf(stderr, "%s: %lu: %s: permission denied\n", progname,
			line_number, cmd);
}
