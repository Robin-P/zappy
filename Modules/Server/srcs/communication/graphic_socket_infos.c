/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** graphic_socket_infos
*/

#include "communication.h"
#include "sockets.h"
#include "client.h"

void remove_client_g(t_server *serv, t_graphical_client *client, bool close_fd)
{
	t_graphical_client *tmp = serv->graphical_client;

	if (client->id == tmp->id)
		serv->graphical_client = client->next;
	else {
		while (tmp->next && tmp->next->id != client->id)
			tmp = tmp->next;
		tmp->next = client->next;
	}
	if (close_fd && is_fd_open(client->socket))
		close(client->socket);
	free(client);
}

int read_on_client_g(t_server *server, t_graphical_client *client)
{
	static char buffer[4096];
	int size;

	size = read(client->socket, buffer, 4096);
	fprintf(stderr, "%i\n", size);
	if (size <= 0)
		return (remove_client_g(server, client, true), ERROR);
	return (SUCCESS);
}