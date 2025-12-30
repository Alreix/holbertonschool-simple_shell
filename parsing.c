#include "shell.h"

/**
 * clean_line - removes trailing newline from a line
 * @line: input line to clean
 */
void clean_line(char *line)
{
	size_t i = 0;

	if (line == NULL)
		return;

	while (line[i] != '\0')
		i++;

	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
}

/**
 * is_blank_line - checks if a line contains only spaces or tabs
 * @line: input string
 *
 * Return: 1 if blank, 0 otherwise
 */
int is_blank_line(char *line)
{
	int i = 0;

	if (line == NULL)
		return (1);

	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
