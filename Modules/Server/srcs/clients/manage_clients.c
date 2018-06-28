/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_clients
*/

#include "client.h"
#include "manage_time.h"
#include "communication.h"

int add_client(t_server *srv)
{
	static size_t id = 0;
	struct sockaddr_in client_sin;
	t_client *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("calloc"), ERROR);
	new->request_number = 0;
	new->team = NULL;
	new->player_id = id++;
	new->socket = accept(srv->socket, (struct sockaddr *)&client_sin,
		&(socklen_t){sizeof(client_sin)});
	new->occupied = false;
	new->last_eat = DEFAULT_VALUE;
	new->inventory = (t_inventory){0, 0, 0, 0, 0, 0, 10, 0};
	new->level = 1;
	new->pos = (t_pos){rand() % srv->opts->x , rand() % srv->opts->y};
	new->look = 1;
	dprintf(new->socket, "WELCOME\n");
	return (new->next = srv->clients, srv->clients = new, SUCCESS);
}

void unlink_client_messages(t_server *server, t_client *client)
{
	t_message *tmp = server->messages;

	while (tmp) {
		if (tmp->owner && tmp->owner->player_id == client->player_id)
			tmp->owner = NULL;
		tmp = tmp->next;
	}
}

void remove_client(t_server *server, t_client *client, bool close_fd)
{
	t_client *tmp = server->clients;
	t_client *save = client;
	char *msg = NULL;

	unlink_client_messages(server, save);
	if (client->player_id == tmp->player_id)
		server->clients = client->next;
	else {
		while (tmp->next && tmp->next->player_id != client->player_id)
			tmp = tmp->next;
		tmp->next = client->next;
	}
	if (close_fd && is_fd_open(client->socket)) {
		asprintf(&msg, "pdi %li", client->player_id);
		send_to_graphics(server, msg);
		dprintf(client->socket, "dead\n");
		close(client->socket);
	}
	free(client);
}

void remove_all_clients(t_client *clients)
{
	t_client *client = clients;

	while (clients) {
		client = clients->next;
		free(clients);
		clients = client;
	}
}

size_t get_clients_number(t_client *clients)
{
	t_client *client = clients;
	size_t i = 0;


	while (client) {
		i += 1;
		client = clients->next;
	}
	return (i);
}
