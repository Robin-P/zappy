/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast
*/

#include "player_actions.h"
#include "communication.h"
#include "manage_time.h"

int switch_diagonal_directions(t_server *server, t_pos owner, t_pos pos)
{
	if (owner.y < pos.y && owner.y - pos.y < server->opts->y / 2)
		return (owner.x > pos.x && owner.x - pos.x
			< server->opts->x / 2 ? 8 : 2);
	else
		return (owner.y > pos.y && owner.y - pos.y
			< server->opts->y / 2 ? 6 : 4);
}

int switch_directions(t_server *server, t_pos owner, t_pos pos)
{
	if (owner.x == pos.x && owner.y == pos.y)
		return (0);
	else if (owner.x == pos.x)
		return (owner.y > pos.y && owner.y - pos.y
			< server->opts->y / 2 ? 5 : 1);
	else if (owner.y == pos.y)
		return (owner.x > pos.x && owner.x - pos.x
			< server->opts->x / 2 ? 7 : 3);
	return (switch_diagonal_directions(server, owner, pos));
}

char *broadcast(t_server *server, t_message *cmd)
{
	t_client *client = server->clients;
	char *response;
	char *tmp;
	int result = 0;

	cmd->finish_date = time_until_finish(BROADCAST_TIME,
					server->opts->freq);
	while (client) {
	if (cmd->owner->player_id != client->player_id && client->team) {
		result = switch_directions(server,
		cmd->owner->pos, client->pos);
		result = (result + 2 * client->look) % 8;
		result = (result == 0 ? 8 : result);
		asprintf(&tmp, "Message %d, %s", result, &cmd->request[11]);
		add_special_response(server, client, tmp);
	}
	client = client->next;
	}
	return (asprintf(&response, "ok"), response);
}
