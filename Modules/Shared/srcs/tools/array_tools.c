/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** array_tools
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "macro.h"
#include "tools.h"

bool arr_contains(const char **haystack, const char *needle)
{
	if (!needle)
		return (false);
	for (int i = 0; haystack[i]; i++)
		if (strcmp(needle, haystack[i]) == 0)
			return (true);
	return (false);
}

int index_in_arr(const char **haystack, const char *needle)
{
	for (int i = 0; haystack[i]; i++)
		if (strcmp(needle, haystack[i]) == 0)
			return (i);
	return (ERR_FC);
}

void free_tab(char **tab)
{
	if (!tab)
		return;
	for (int i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

char **str_to_tab(char *str, const char *delimiter)
{
	char **tab = NULL;
	char *tmp = NULL;
	int i = 0;

	if (!str || !delimiter)
		return (NULL);
	tab = calloc(count_words(str, (char *)delimiter) + 2, sizeof(char *));
	if (!tab)
		return (FCT_FAILED("calloc"), NULL);
	tmp = strtok(str, delimiter);
	tab[i] = strdup(tmp);
	while (tmp != NULL) {
		tmp = strtok(NULL, delimiter);
		if (!tmp)
			break;
		tab[++i] = strdup(tmp);
	}
	tab[i + 1] = NULL;
	return (tab);
}

void show_tab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		printf("%s\n", tab[i]);
}