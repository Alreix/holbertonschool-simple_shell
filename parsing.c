#include "shell.h"

/**
 * clean_line - removes trailing newline from a line
 * @line: input line to clean
 */
void clean_line(char *line)
{
	size_t i = 0, start = 0, end;

	if (line == NULL)
		return;

	while (line[i] != '\0')
		i++;

	if (i > 0 && line[i - 1] == '\n')
	{
		line[i - 1] = '\0';
		i--;
	}

	end = i;
	while (end > 0 && (line[end - 1] == ' ' || line[end - 1] == '\t'))
		end--;
	line[end] = '\0';

	while (line[start] == ' ' || line[start] == '\t')
		start++;

	if (start > 0)
	{
		i = 0;
		while (line[start + i])
		{
			line[i] = line[start + i];
			i++;
		}
		line[i] = '\0';
	}
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
