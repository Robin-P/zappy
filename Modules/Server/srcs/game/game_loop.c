/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game_loop
*/

#include "communication.h"
#include "manage_time.h"
#include "client.h"
#include "game.h"

static t_client *player_starving_to_death(t_server *server,
					t_client *dead_man)
{
	t_client *save;

	if (dead_man->team && dead_man->inventory.food == 0) {
		save = dead_man->next;
		remove_client(server, dead_man, true);
		return (save);
	}
	return (dead_man->next);
}


static void lost_lives(t_server* server, t_client *clients)
{
	t_client *tmp = clients;

	while (tmp) {
		if (is_finish(tmp->last_eat)) {
			tmp->inventory.food -= 1;
			tmp->last_eat = time_until_finish(
				LIFE_TIME, server->opts->freq);
			tmp = player_starving_to_death(server, tmp);
		} else
			tmp = tmp->next;
	}
}

static void check_incantations_state(t_server *s, t_message *messages)
{
	t_message *t = messages;
	char *m = NULL;

	while (t) {
	if (t->request && strcmp(t->request, "Incantation") == 0 &&
	!t->response && t->owner && is_finish(t->finish_date)) {
	if (s->map[t->owner->pos.y][t->owner->pos.x].incantation &&
	is_inventory_complete(s, t->owner)) {
	asprintf(&t->response, "Current level: %ld",
	++t->owner->level);
	reset_inventory(t->owner);
	asprintf(&m, "plv %li %li", t->owner->player_id, t->owner->level);
	send_to_graphics(s, m);
	if (t->owner->level == MAX_LEVEL)
		s->continue_game = false;
	} else
		asprintf(&t->response, "ko");
	}
	t = t->next;
	}
}

int game_loop(t_server *server)
{
	while (server->continue_game) {
		if (manage_sockets(server) == ERROR)
			return (ERROR);
		lost_lives(server, server->clients);
		read_all_messages(server, server->messages);
		check_incantations_state(server, server->messages);
		send_responses(server, server->messages);
		spawn_object(server, false);
	}
	return (SUCCESS);
}
