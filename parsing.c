#include "shell.h"
#include <string.h>
#include <stdlib.h>

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
/**
 * free_tokens - frees tokens array returned by split_line
 * @tokens: tokens array to free
 */
void free_tokens(char **tokens)
{
	free(tokens);
}

/**
 * split_line - splits a line into tokens
 * @line: input line to split (will be modified by strtok)
 * @separator: set of delimiters (example: " \t")
 *
 * Return: malloc'd tokens array, or NULL on failure
 */
char **split_line(char *line, char *separator)
{
	char *token;
	char **tokens, **new_tokens;
	int buffer_size = 10, i = 0;

	tokens = malloc(sizeof(char *) * buffer_size);
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, separator);
	if (token == NULL)
	{
		free(tokens);
		return (NULL);
	}
	while (token != NULL)
	{
		if (i + 1 >= buffer_size)
		{
			buffer_size *= 2;
			new_tokens = realloc(tokens, sizeof(char *) * buffer_size);
			if (new_tokens == NULL)
			{
				free(tokens);
				return (NULL);
			}
			tokens = new_tokens;
		}

		tokens[i] = token;
		i++;
		token = strtok(NULL, separator);
	}
	tokens[i] = NULL;

	return (tokens);
}
