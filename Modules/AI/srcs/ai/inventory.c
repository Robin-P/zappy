/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory
*/

#include "ai.h"
#include "macro.h"
#include "commands.h"

static void put_in_inventory(t_ai *ai, char **tmp)
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
			ai->inv[action[j].elem] = atoi(tmp[1]);
			break;
		}
	}
}

static void parse_inventory(t_ai *ai, char *s)
{
	char **tab = str_to_tab(s, ",");
	char **tmp = NULL;

	if (!tab)
		return;
	for (int i = 0; tab[i]; i++) {
		tab[i] = lstrip_m(tab[i], "[ ");
		tmp = str_to_tab(tab[i], " ");
		put_in_inventory(ai, tmp);
		free_tab(tmp);
	}
	free_tab(tab);
}

int inventory(t_ai *ai, char *s)
{
	parse_inventory(ai, s);
	for (int i = 0; i < INVENT_SIZE; i++)
		printf("%ld  ", ai->inv[i]);
	printf("\n");
	return (SUCCESS);
}