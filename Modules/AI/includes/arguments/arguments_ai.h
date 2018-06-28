/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** arguments
*/

#pragma once

#include <stdbool.h>
#include "tools.h"

typedef struct s_opts_ai {
	int port;
	char *name;
	char *machine;
	t_vec2d dim;
} t_opts_ai;

typedef struct s_args {
	char *flag;
	int (*function)(char **, t_opts_ai *);
} t_args;

int manage_commands(char **, t_opts_ai *);

int help(char **, t_opts_ai *);
int port(char **, t_opts_ai *);
int name(char **, t_opts_ai *);
int machine(char **, t_opts_ai *);

bool check_commands(t_opts_ai *);