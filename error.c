#include "shell.h"

/**
 * print_not_found - prints a "not found" error message
 * @progname: program name (argv[0])
 * @line_number: input line number (non-interactive)(unused here)
 * @cmd: command name that was not found (unused here)
 */
void print_not_found(char *progname, unsigned long line_number, char *cmd)
{
	(void)line_number;
	(void)cmd;

	if (progname == NULL)
		return;

	perror(progname);
}
