/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include "macro.h"
#include "arguments_server.h"
#include "tools.h"
#include "sockets.h"
#include "map.h"

typedef struct s_graphical_client {
	int socket;
	size_t id;
	struct s_graphical_client *next;
} t_graphical_client;

typedef struct s_client {
	int socket;
	t_team *team;
	size_t player_id;
	size_t request_number;
	t_inventory inventory;
	t_pos pos;
	long long last_eat;
	size_t level;
	size_t look;
	bool occupied;
	struct s_client *next;
} t_client;

typedef struct s_message {
	size_t id;
	t_client *owner;
	char *request;
	char *response;
	char *graphics_message;
	long long finish_date;
	struct s_message *next;
} t_message;

typedef struct s_egg {
	size_t id;
	t_client *hen;
	t_team *team;
	t_pos pos;
	long long finish_date;
	struct s_egg *next;
} t_egg;

typedef struct s_server {
	t_opts *opts;
	t_egg *eggs;
	t_inventory **map;
	t_client *clients;
	t_graphical_client *graphical_client;
	t_message *messages;
	int socket;
	bool continue_game;
} t_server;

typedef struct s_time {
	long long time;
	int loop_time;
} t_time;

size_t count_row(char **array);
bool add_team_member(t_server *server, char *team_name);
bool remove_team_member(t_server *server, char *team_name);
bool init_team(t_server *server);

char *get_map_objects_top_bot(t_server *, char *, t_pos, t_message *cmd);
char *get_map_objects_left_right(t_server *, char *, t_pos, t_message *cmd);

void spawn_object(t_server *server, bool to_free);