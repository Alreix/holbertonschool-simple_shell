#include "shell.h"

/**
 * print_not_found - prints a "not found" error message
 * @progname: program name (argv[0])
 * @line_number: input line number (non-interactive)
 * @cmd: command name that was not found
 * @interactive: 1 if interactive mode, 0 otherwise
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
		fprintf(stderr, "%s: %lu: %s: not found\n", progname, line_number, cmd);
}
