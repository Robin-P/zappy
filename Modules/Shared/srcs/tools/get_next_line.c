/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** get_next_line
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"


static char get_next_char(const int fd)
{
	static char buffer[READ_SIZE + 1];
	static int size = 0;
	static int i = 0;
	char my_char;

	if (size == 0) {
		size = read(fd, buffer, READ_SIZE);
		if (size == 0)
			return ('\0');
		i = 0;
	}
	my_char = buffer[i];
	i++;
	size--;
	return (my_char);
}

static char *my_realloc(char *str)
{
	char *new_str;
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	new_str = malloc(sizeof(char) * (i + READ_SIZE + 1));
	if (!new_str)
		return (NULL);
	new_str[i] = '\0';
	i = 0;
	while (str[i] != '\0') {
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static char *freell(char *line)
{
	free(line);
	return (NULL);
}

char *get_next_line(const int fd)
{
	char *line = calloc(READ_SIZE + 1, sizeof(char));
	char my_char;
	int i = 0;

	if (!line)
		return (NULL);
	my_char = get_next_char(fd);
	while (my_char != '\n' && my_char != '\0') {
		line[i++] = my_char;
		my_char = get_next_char(fd);
		if (i % (READ_SIZE) == 0) {
			line[i] = '\0';
			line = my_realloc(line);
			if (!line)
				return (NULL);
		}
	}
	return (line[i] = '\0', my_char == '\0' &&
		line[0] == '\0' ? freell(line) : line);
}