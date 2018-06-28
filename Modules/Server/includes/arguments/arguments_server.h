/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** arguments
*/

#pragma once

typedef struct s_team {
	char *name;
	size_t id;
} t_team;

typedef struct s_opts {
	int port;
	int x;
	int y;
	t_team **teams;
	int max_clients;
	int freq;
} t_opts;

typedef struct s_args {
	char *flag;
	int (*function)(char **, t_opts *);
} t_args;

int manage_command(const int, char **, t_opts *);
void remove_all_teams(t_team **);

int port(char **, t_opts *);
int width(char **, t_opts *);
int height(char **, t_opts *);
int name(char **, t_opts *);
int clients(char **, t_opts *);
int freq(char **, t_opts *);
int usage(char **, t_opts *);