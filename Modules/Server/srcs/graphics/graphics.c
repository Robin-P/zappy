/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** graphics
*/

#include "communication.h"
#include "manage_time.h"
#include "server.h"
#include "client.h"

static t_graphical_client *client_to_graphical(
		t_server *server, t_client *client)
{
	static size_t id = 0;
	t_graphical_client *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), NULL);
	printf("New graphical client - %ld\n", id);
	new->id = id++;
	new->socket = client->socket;
	new->next = server->graphical_client;
	server->graphical_client = new;
	return (new);
}

static void send_map_status(t_server *server, const int socket)
{
	t_inventory c;

	for (size_t i = 0 ; server->opts->teams[i] ; i++)
		dprintf(socket, SEND_TEAM, server->opts->teams[i]->name);
	for (int i = 0 ; i < server->opts->y ; i++)
		for (int f = 0 ; f < server->opts->x  ; f++) {
			c = server->map[i][f];
			dprintf(socket, SEND_CELL, f, i, c.food, c.linemate,
		c.deraumere, c.sibur, c.mendiane, c.phiras, c.thystame);
			usleep(200);
		}
	for (t_egg *egg = server->eggs ; egg ; egg = egg->next)
		dprintf(socket, SEND_EGG, egg->id, egg->hen->player_id,
			egg->pos.x, egg->pos.y);
	for (t_client *cli = server->clients ; cli ; cli = cli->next)
		dprintf(socket, SEND_CLIENT, cli->player_id, cli->pos.x,
			cli->pos.y, cli->look, cli->level, cli->team->name);
}

void is_graphical(t_server *server, t_client *client)
{
	t_graphical_client *g_client;
	g_client = client_to_graphical(server, client);
	remove_client(server, client, false);
	dprintf(g_client->socket, "msz %d %d\n",
		server->opts->x, server->opts->y);
	send_map_status(server, g_client->socket);
}

void remove_all_graphics_clients(t_graphical_client *clients)
{
	t_graphical_client *client = clients;

	while (clients) {
		client = clients->next;
		free(clients);
		clients = client;
	}
}