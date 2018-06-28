/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_actions
*/

#pragma once

#include "server.h"

typedef struct s_ptr_action {
	char *(*fct)(t_server *, t_message *);
	char *cmd;
} t_ptr_action;

char *forward(t_server *, t_message *);
char *right(t_server *, t_message *);
char *left(t_server *, t_message *);
char *look(t_server *, t_message *);
char *inventory(t_server *, t_message *);
char *broadcast(t_server *, t_message *);
char *connect_number(t_server *, t_message *);
char *fork_cmd(t_server *, t_message *);
char *eject(t_server *, t_message *);
char *take_obj(t_server *, t_message *);
char *set_obj(t_server *, t_message *);
char *incantation(t_server *, t_message *);
char *fork_cmd(t_server *, t_message *);