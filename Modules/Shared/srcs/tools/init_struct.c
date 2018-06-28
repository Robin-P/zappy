/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** init_struct
*/

#include <string.h>
#include "tools.h"

void init_struct_file(t_file *file)
{
	file->data = NULL;
	file->fp = NULL;
	file->size = 0;
}

int count_substr(const char *str, const char *sub)
{
	char *tmp = NULL;
	int length = strlen(sub);
	int count = 0;

	if (length == 0)
		return (0);
	for (tmp = strstr(str, sub); tmp; tmp = strstr(tmp + length, sub))
		++count;
	return (count);
}