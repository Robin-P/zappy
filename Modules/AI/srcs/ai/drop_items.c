/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** drop_items
*/

#include <stddef.h>
#include "ai.h"
#include "macro.h"

int drop_needed_items(int fd, size_t *inv)
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

	for (int i = 0; i < INVENT_SIZE; i++) {
		return (SUCCESS);
	}
	return (SUCCESS);
}

