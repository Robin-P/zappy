/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_client
*/

#include "client.h"
#include "manage_time.h"

t_change_map *get_tab(t_server *server, t_message *cmd)
{
	t_change_map *tab;
	tab = malloc(sizeof(t_change_map) * 8);
	tab[0] = (t_change_map){&cmd->owner->inventory.food, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].food, "food"};
	tab[1] = (t_change_map){&cmd->owner->inventory.linemate, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].linemate, "linemate"};
	tab[2] = (t_change_map){&cmd->owner->inventory.deraumere, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].deraumere, "deraumere"};
	tab[3] = (t_change_map){&cmd->owner->inventory.sibur, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].sibur, "sibur"};
	tab[4] = (t_change_map){&cmd->owner->inventory.mendiane, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].mendiane, "mendiane"};
	tab[5] = (t_change_map){&cmd->owner->inventory.phiras, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].phiras, "phiras"};
	tab[6] = (t_change_map){&cmd->owner->inventory.thystame, &server->map
	[cmd->owner->pos.y][cmd->owner->pos.x].thystame, "thystame"};
	tab[7] = (t_change_map){NULL};
	return (tab);
}

char *take_obj(t_server *server, t_message *cmd)
{
	char *str, *line;
	t_change_map *tab;

	asprintf(&line, "%s", &cmd->request[5]);
	tab = get_tab(server, cmd);
	for (int i = 0; i < 7; ++i)
		if (strcmp(line, tab[i].str) == 0
		&& *(tab[i].x) > 0) {
			cmd->finish_date =
			time_until_finish(TAKE_TIME, server->opts->freq);
			*(tab[i].inv) += 1;
			*(tab[i].x) -= 1;
			asprintf(&server->messages->graphics_message,
			"pgt %li %li", cmd->owner->player_id, *tab[i].inv);
			return (asprintf(&str, "ok"), free(tab),
			free(line), str);
		}
	return (free(tab), free(line), NULL);
}

char *set_obj(t_server *server, t_message *cmd)
{
	char *str, *line;
	t_change_map *tab;

	asprintf(&line, "%s", &cmd->request[4]);
	tab = get_tab(server, cmd);
	if (strlen(line) <= 4)
		return (asprintf(&str, "ko"), free(tab), free(line), NULL);
	for (int i = 0; i < 7; ++i)
		if (strcmp(line, tab[i].str) == 0
		&& *(tab[i].inv) > 0) {
			cmd->finish_date =
			time_until_finish(SET_TIME, server->opts->freq);
			*(tab[i].inv) -= 1;
			*(tab[i].x) += 1;
			asprintf(&server->messages->graphics_message,
			"pdr %li %i", cmd->owner->player_id, 1);
			return (asprintf(&str, "ok"), free(tab),
			free(line), str);
		}
	return (asprintf(&str, "ko"), free(tab), free(line), NULL);
}
