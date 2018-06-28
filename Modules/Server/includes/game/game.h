/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game
*/

#pragma once

#include "server.h"

void reset_inventory(t_client *);
bool is_inventory_complete(t_server *, t_client *);

int manage_sockets(t_server *);
int game_loop(t_server *);