/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation
*/

#include "tools.h"
#include "server.h"
#include "manage_time.h"
#include "communication.h"

static size_t clients_on_cell(t_server *server, t_pos *pos, size_t level)
{
	t_client *tmp = server->clients;
	size_t nb_players = 0;

	while (tmp) {
		if (tmp->pos.x == pos->x &&
		tmp->pos.y == pos->y &&
		tmp->level == level)
			nb_players += 1;
		tmp = tmp->next;
	}
	return (nb_players);
}

void reset_inventory(t_client *player)
{
	player->inventory.deraumere = 0;
	player->inventory.linemate = 0;
	player->inventory.mendiane = 0;
	player->inventory.phiras = 0;
	player->inventory.sibur = 0;
	player->inventory.thystame = 0;
	player->inventory.incantation = false;
}

bool is_inventory_complete(t_server *server, t_client *player)
{
	t_inventory inv = player->inventory;
	const size_t *needed = g_elevation[player->level - 1];

	return (needed[EL_DERAUMERE] == inv.deraumere &&
		needed[EL_LINEMATE] == inv.linemate &&
		needed[EL_MENDIANE] == inv.mendiane &&
		needed[EL_PHIRAS] == inv.phiras &&
		needed[EL_SIBUR] == inv.sibur &&
		needed[EL_THYSTAME] == inv.thystame &&
		needed[EL_PLAYER] == clients_on_cell(server,
		&player->pos, player->level));
}

char *incantation(t_server *server, t_message *cmd)
{
	bool level_up = is_inventory_complete(server, cmd->owner);

	cmd->finish_date = (level_up ? time_until_finish(
		INCANTATION_TIME, server->opts->freq) : 0);
	server->map[cmd->owner->pos.y][
		cmd->owner->pos.x].incantation = (level_up ? true : false);
	add_special_response(server, cmd->owner, strdup(
		(level_up ? START_ELEVATION : ELEVATION_FAILED)));
	return (NULL);
}
