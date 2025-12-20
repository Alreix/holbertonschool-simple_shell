#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * free_tokens - frees tokens array returned by split_line
 * @tokens: tokens array to free
 */
void free_tokens(char **tokens)
{
	free(tokens);
}

/**
 * split_line - splits a line into tokens (spaces/tabs supported)
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
