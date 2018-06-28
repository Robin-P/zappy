/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** graphic_clients
*/

#include "server.h"

void send_to_graphics(t_server *server, char *msg)
{
	t_graphical_client *tmp = server->graphical_client;

	while (tmp) {
		dprintf(tmp->socket, "%s\n", msg);
		tmp = tmp->next;
	}
	free(msg);
}