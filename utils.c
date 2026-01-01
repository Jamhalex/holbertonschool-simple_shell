#include "shell.h"

/**
 * strip_newline - removes trailing newline if present
 * @s: string to edit
 */
void strip_newline(char *s)
{
	size_t i;

	if (s == NULL)
		return;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			return;
		}
	}
}

/**
 * trim_spaces - trims leading and trailing spaces/tabs
 * @s: string to trim
 *
 * Return: pointer to first non-space char (inside s)
 */
char *trim_spaces(char *s)
{
	size_t end;
	char *start;

	if (s == NULL)
		return (NULL);

	start = s;
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (start);

	end = strlen(start);
	while (end > 0 && (start[end - 1] == ' ' || start[end - 1] == '\t'))
	{
		start[end - 1] = '\0';
		end--;
	}

	return (start);
}

