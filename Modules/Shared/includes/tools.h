/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tools
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/*
** Structures
*/

typedef enum {
	EL_PLAYER,
	EL_LINEMATE,
	EL_DERAUMERE,
	EL_SIBUR,
	EL_MENDIANE,
	EL_PHIRAS,
	EL_THYSTAME
} e_element;

typedef struct s_vec2d {
	int x;
	int y;
} t_vec2d;

typedef struct s_file {
	FILE *fp;
	char *data;
	size_t size;
} t_file;

typedef struct s_elevation {
	size_t player;
	size_t linemate;
	size_t deraumere;
	size_t sibur;
	size_t mendiane;
	size_t phiras;
	size_t thystame;
} t_elevation;

static const size_t g_elevation[7][7] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};

bool arr_contains(const char **, const char *);
int index_in_arr(const char **, const char *);
void free_tab(char **);
char **str_to_tab(char *, const char *);
void show_tab(char **);

char *lstrip(char *, char *);
char *rstrip(char *, char *);
char *lstrip_m(char *, char *);
char *rstrip_m(char *, char *);
char char_to_upper(char);
void str_to_upper(char *);
int count_words(char *, char *);
bool is_number(char *);
void replace_str(char *, const char *, const char *);
void insert(char *, const char *, int);
size_t tablen(char **);
void init_struct_file(t_file *);

int count_substr(const char *, const char *);
char *replace(char *, const char *, const char *);
char *mallocat(char *, const char *, const char *);