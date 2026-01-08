#include "shell.h"

/**
 * read_command - reads one command line from stdin
 * @line: address of the buffer used by getline
 * @buf_size: address of the buffer size for getline
 * @interactive: 1 if stdin is a terminal, 0 otherwise
 * @line_number: address of the current input line number
 *
 * Return: number of bytes read, or -1 on EOF/error
 */
ssize_t read_command(char **line, size_t *buf_size, int interactive,
		int *line_number)
{
	ssize_t read_line;

	read_line = getline(line, buf_size, stdin);
	if (read_line == -1)
	{
		if (interactive)
			printf("\n");
		return (-1);
	}

	(*line_number)++;
	clean_line(*line);

	return (read_line);
}

/**
 * handle_line - parses and executes a command line
 * @line: input line (will be modified by strtok)
 * @env: environment variables
 * @progname: argv[0] (program name for errors)
 * @line_number: current input line number
 *
 * Return: command exit status, or 1 on internal error
 */
int handle_line(char *line, char **env, char *progname,
		int line_number)
{
	char **argv;
	int status;

	if (is_blank_line(line))
		return (0);

	argv = split_line(line, " \t");
	if (argv == NULL)
		return (1);

	if (argv[0] == NULL || argv[0][0] == '\0')
	{
		free_tokens(argv);
		return (0);
	}

	if (exit_cmd(argv))
	{
		free_tokens(argv);
		return (-2);
	}

	if (env_cmd(argv))
	{
		print_env(env);
		free_tokens(argv);
		return (0);
	}

	status = exec_with_path(argv, env, progname, line_number);
	free_tokens(argv);

	return (status);
}
