/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** replace
*/

#include <stdlib.h>
#include <string.h>
#include "tools.h"

static int count_sub(const char *s, const char *sub)
{
	int count = 0;

	for (int i = 0; s[i]; i++)
		if (strstr(&s[i], sub) == &s[i]) {
			count++;
			i += strlen(sub);
		}
	return (count);
}

char *replace(char *s, const char *old, const char *new)
{
	char *res;
	int i = 0;
	int cnt = count_sub(s, old);

	if (!s)
		return (NULL);
	if (cnt == 0)
		return (s);
	res = calloc(i + cnt * (strlen(old) - strlen(new)) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (*s) {
		if (strstr(s, old) == s) {
			strcpy(&res[i], new);
			i += strlen(new);
			s += strlen(old);
		} else
			res[i++] = *s++;
	}
	return (res[i] = '\0', res);
}