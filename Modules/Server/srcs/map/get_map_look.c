/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include "macro.h"
#include "server.h"

char *comma(const t_get_type tab[7], char *str, int nb)
{
	for (int i = nb; i < 7;++i) {
		if (tab[i].x > 0 && strlen(str) > 2) {
			str = mallocat(str, " ", "");
			break;
		}
	}
	return (str);
}

char *players_pos(t_server *server, char *str, t_pos pos)
{
	t_client *tmp = server->clients;

	while (tmp) {
		if (tmp->pos.x == pos.x && tmp->pos.y == pos.y)
			str = mallocat(str, " player", "");
		tmp = tmp->next;
	}
	return (str);
}

char *push_str(t_server *server, char *str, t_pos pos, t_message *cmd)
{
	static int x = 0;
	const t_get_type tab[7] = {{server->map[pos.y][pos.x].food, "food"},
	{server->map[pos.y][pos.x].linemate, "linemate"},
	{server->map[pos.y][pos.x].deraumere, "deraumere"},
	{server->map[pos.y][pos.x].sibur, "sibur"},
	{server->map[pos.y][pos.x].mendiane, "mendiane"},
	{server->map[pos.y][pos.x].phiras, "phiras"},
	{server->map[pos.y][pos.x].thystame, "thystame"}};

	str = comma(tab, players_pos(server, str, pos), 0);
	for (int i = 0; i < 7;++i)
		if (tab[i].x > 0) {
		for (size_t j = 0; j < tab[i].x; ++j)
		str = mallocat(str, tab[i].str, (j + 1 < tab[i].x ? " " : ""));
		str = comma(tab, str, i + 1);
		}
	if (x < (int)(3 * cmd->owner->level + (2 * (cmd->owner->level - 1))))
		str = mallocat(str, ",", "");
	else
		x = -1;
	return (++x, str);
}

char *get_map_objects_top_bot(t_server *server,
				char *str, t_pos pos, t_message *cmd)
{
	int x;
	int y;

	if (pos.x < 0) {
		y = pos.y;
		x = server->opts->x + pos.x;
	}
	else if (pos.x > server->opts->x - 1) {
		y = pos.y;
		x = pos.x - server->opts->x;
	}
	else {
		y = pos.y;
		x = pos.x;
	}
	str = push_str(server, str, (t_pos){x, y}, cmd);
	return (str);
}

char *get_map_objects_left_right(t_server *server,
				char *str, t_pos pos, t_message *cmd)
{
	int x;
	int y;

	if (pos.y < 0) {
		y = server->opts->y + pos.y;
		x = pos.x;
	}
	else if (pos.y > server->opts->y - 1) {
		y = pos.y - server->opts->y;
		x = pos.x;
	}
	else {
		y = pos.y;
		x = pos.x;
	}
	str = push_str(server, str, (t_pos){x, y}, cmd);
	return (str);
}
