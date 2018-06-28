/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** string_tools
*/

#include <string.h>
#include <stdlib.h>
#include "macro.h"

char char_to_upper(char c)
{
	return (c >= 'a' && c <= 'z' ? c - 32 : c);
}

void str_to_upper(char *str)
{
	if (!str)
		return;
	for (; *str != '\0'; str++)
		*str = char_to_upper(*str);
}

int count_words(char *str, char *delimiter)
{
	int state = 0;
	int count = 0;

	while (*str) {
		if (strchr(delimiter, *str))
			state = 0;
		else if (state == 0) {
			state = 1;
			++count;
		}
		++str;
	}
	return (count);
}

char *mallocat(char *dest, const char *src, const char *endline)
{
	int f = 0;
	char *new = calloc(strlen(dest) + strlen(src) + strlen(endline) + 1,
			sizeof(*new));

	if (!new)
		return (NULL);
	for (int i = 0 ; dest[i] ; i++, f++)
		new[f] = dest[i];
	for (int i = 0 ; src[i] ; i++, f++)
		new[f] = src[i];
	for (int i = 0 ; endline[i] ; i++, f++)
		new[f] = endline[i];
	free(dest);
	return (new);
}