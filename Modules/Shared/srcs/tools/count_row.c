/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

size_t count_row(char **array)
{
	size_t lenght = 0;

	if (!array)
		return (0);
	for (size_t i = 0 ; array[i] != NULL ; ++i);
	return (lenght);
}

size_t tablen(char **tab)
{
	size_t i = 0;

	if (!tab) return (i);
	for (; tab[i]; i++);
	return (i);
}

bool is_number(char *s)
{
	if (!s)
		return (false);
	for (int i = 0; s[i]; i++)
		if (!isdigit(s[i]))
			return (false);
	return (true);
}

void insert(char *subject, const char *insert, int pos) {
	char buf[4096] = {};

	strncpy(buf, subject, pos);
	int len = strlen(buf);
	strcpy(buf+len, insert);
	len += strlen(insert);
	strcpy(buf+len, subject+pos);

	strcpy(subject, buf);
}

void replace_str(char *str, const char *find, const char *rep)
{
	for (int i = 0; str[i]; i++)
		if (strncmp(&str[i], find, strlen(find)) == 0)
			insert(str, rep, i + 1);
}
