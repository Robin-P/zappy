/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ai.h"
#include "macro.h"
#include "tools.h"
#include "commands.h"

bool compare_elevation(const size_t *left, const size_t *right)
{
	return (left[EL_PLAYER] == right[EL_PLAYER] &&
		left[EL_DERAUMERE] == right[EL_DERAUMERE] &&
		left[EL_LINEMATE] == right[EL_LINEMATE] &&
		left[EL_MENDIANE] == right[EL_MENDIANE] &&
		left[EL_PHIRAS] == right[EL_PHIRAS] &&
		left[EL_SIBUR] == right[EL_SIBUR] &&
		left[EL_THYSTAME] == right[EL_THYSTAME]);
}

static void put_in_inventory(size_t *inv, char **tmp)
{
	static const t_action action[] = {
		{"linemate", EL_LINEMATE},
		{"deraumere", EL_DERAUMERE},
		{"mendiane", EL_MENDIANE},
		{"phiras", EL_PHIRAS},
		{"sibur", EL_SIBUR},
		{"thystame", EL_THYSTAME},
		{"player", EL_PLAYER},
		{NULL}
	};

	for (int j = 0; action[j].str; j++) {
		if (strcmp(action[j].str, tmp[0]) == 0) {
			inv[action[j].elem] = atoi(tmp[1]);
			break;
		}
	}
}

static void get_number_player(t_ai *ai)
{
	char *res = NULL;
	char **tmp = NULL;

	send_command(ai, LOOK);
	res = readline(ai->fd);
	tmp = str_to_tab(res, ",");
	tmp[0] = lstrip(tmp[0], "[ ");
	ai->inv[EL_PLAYER] = count_substr(tmp[0], "player");
	free_tab(tmp);
}

static size_t *parse_inventory(t_ai *ai, char *buf)
{
	static size_t inv[7] = {0};
	char **tab = str_to_tab(buf, ",");
	char **tmp = NULL;

	for (int i = 0; tab[i]; i++) {
		tab[i] = lstrip(tab[i], "[ ");
		tmp = str_to_tab(tab[i], " ");
		put_in_inventory(inv, tmp);
		free_tab(tmp);
	}
	free_tab(tab);
	get_number_player(ai);
	return (inv);
}

int try_incantation(t_ai *ai)
{
	size_t *inv = NULL;
	char *buf;

	send_command(ai, INVENTORY);
	buf = readline(ai->fd);
	printf("%s\n", buf);
	if (buf) {
		send_command(ai, LOOK);
		wait_for_response(ai);
		inv = parse_inventory(ai, buf);
		free(buf);
		if (compare_elevation(inv, g_elevation[ai->level])) {
			ai->level++;
			send_command(ai, START_INCANTATION);
			// drop_needed_items(ai->fd, inv);
		}
		return (SUCCESS);
	}
	return (ERROR);
}