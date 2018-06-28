/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_client
*/

#include "client.h"
#include "manage_time.h"
#include "communication.h"

static void move_eject(t_opts *opts, t_client *client, size_t look)
{
	switch (look) {
		case 0:
		client->pos.y -= (client->pos.y <= 0 ? -opts->y + 1 : 1);
		break;
		case 1:
		client->pos.x += (client->pos.x >=
		opts->x - 1? -opts->x + 1 : 1);
		break;
		case 2:
		client->pos.y += (client->pos.y >=
		opts->y - 1? -opts->y + 1 : 1);
		break;
		case 3:
		client->pos.x -= (client->pos.x <= 0 ? -opts->x + 1 : 1);
		break;
	}
}

char *eject(t_server *server, t_message *cmd)
{
	char *str;
	char *tmp;
	t_client *client = server->clients;

	cmd->finish_date = time_until_finish(EJECT_TIME, server->opts->freq);
	while (client) {
		if (client->player_id != cmd->owner->player_id
		&& client->pos.y == cmd->owner->pos.y
		&& client->pos.x == cmd->owner->pos.x) {
			asprintf(&server->messages->graphics_message,
				"pex %li", cmd->owner->player_id);
			move_eject(server->opts, client, cmd->owner->look);
			asprintf(&tmp, "Eject: %ld", cmd->owner->look);
			add_special_response(server, client, tmp);
		}
		client = client->next;
	}
	return (asprintf(&str, "ok"), str);
}