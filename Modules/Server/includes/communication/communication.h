/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** communication
*/

#pragma once

#include "server.h"
#include "client.h"

int read_on_client_g(t_server *server, t_graphical_client *client);
int add_message_in_list(t_server *, t_client *, const char *);
int add_special_response(t_server *, t_client *, char *);
void read_all_messages(t_server *, t_message *);
void send_responses(t_server *, t_message *);
void send_all(const t_server *, const t_client *, const char *);
t_message *remove_messages(t_server *, t_message *);
void remove_all_messages(t_server *);
void parse_command(t_server *, t_message *);
void unlink_client_messages(t_server *, t_client *);
void send_to_graphics(t_server *server, char *msg);