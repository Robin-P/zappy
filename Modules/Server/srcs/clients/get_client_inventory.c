/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_client
*/

#include "client.h"
#include "manage_time.h"

char *inventory(t_server *server, t_message *cmd)
{
	char *str;
	const t_get_type tab[7] = {{cmd->owner->inventory.food, "food"},
	{cmd->owner->inventory.linemate, "linemate"},
	{cmd->owner->inventory.deraumere, "deraumere"},
	{cmd->owner->inventory.sibur, "sibur"},
	{cmd->owner->inventory.mendiane, "mendiane"},
	{cmd->owner->inventory.phiras, "phiras"},
	{cmd->owner->inventory.thystame, "thystame"}};

	cmd->finish_date = time_until_finish(INVENTORY_TIME,
	server->opts->freq);
	asprintf(&str, "[");
	for (int i = 0; i < 7;++i) {
		asprintf(&str, "%s%s %ld", str, tab[i].str, tab[i].x);
		if (i < 6)
			asprintf(&str, "%s, ", str);
	}
	asprintf(&str, "%s]", str);
	return (str);
}