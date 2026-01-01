#include "shell.h"
#include <stdio.h>

/**
 * print_prompt - prints the shell prompt in interactive mode
 *
 * Return: 0 on success
 */

int print_prompt(void)
{
	printf("($) ");
	fflush(stdout);
	return (0);
}
