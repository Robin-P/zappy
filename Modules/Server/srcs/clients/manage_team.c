/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_team
*/

#include <communication.h>
#include "eggs.h"
#include "manage_time.h"

size_t places_in_client_team(t_server *server, t_client *owner)
{
	t_client *client = server->clients;
	size_t i = server->opts->max_clients;

	while (client) {
		if (owner->team && client->team &&
		owner->team->id == client->team->id)
			i -= 1;
		client = client->next;
	}
	return (i);
}

int player_in_team(t_server *server, t_team *team)
{
	t_client *client = server->clients;
	size_t i = 0;

	while (client) {
		if (team && client->team && team->id == client->team->id)
			i += 1;
		client = client->next;
	}
	return (i);
}

char *connect_number(t_server *server, t_message *cmd)
{
	char *response;

	cmd->finish_date = time_until_finish(0, server->opts->freq);
	asprintf(&response, "%ld", places_in_client_team(server, cmd->owner));
	return (response);
}

bool find_free_egg(t_server *server, t_team *team, size_t *egg_id)
{
	t_egg *tmp = server->eggs;

	while (tmp) {
		if (team->id == tmp->team->id && is_finish(tmp->finish_date)) {
			*egg_id = tmp->id;
			remove_egg(server, tmp);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void find_team(t_server *s, t_client *c, const char *n)
{
	t_team **t = s->opts->teams;
	char *msg = NULL;
	int p;
	size_t e = 0;

	for (int i = 0 ; t[i] ; i++) {
	p = player_in_team(s, t[i]);
	if (strcmp(t[i]->name, n) == 0 && p < s->opts->max_clients) {
		if (!find_free_egg(s, t[i], &e) && p != 0)
			break;
	c->team = t[i];
	dprintf(c->socket, "%ld\n", places_in_client_team(s, c));
	dprintf(c->socket, "%d %d\n", s->opts->x, s->opts->y);
	c->last_eat = time_until_finish(LIFE_TIME, s->opts->freq);
	asprintf(&msg, "eht %li\npnw %li %i %i %li %li %s", e, c->player_id,
	c->pos.x, c->pos.y, c->look, c->level, c->team->name);
	return send_to_graphics(s, msg);
	}
	}
	add_special_response(s, c, strdup("ko"));
}
