/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_eggs
*/

#include "server.h"
#include "manage_time.h"

int add_egg(t_server *server, t_client *hen)
{
	static size_t id = 0;
	t_egg *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("calloc"), ERROR);
	new->finish_date = time_until_finish(HATCH_TIME, server->opts->freq);
	new->id = id;
	new->pos = hen->pos;
	new->hen = hen;
	new->team = hen->team;
	new->next = server->eggs;
	server->eggs = new;
	id += 1;
	return (SUCCESS);
}

void remove_egg(t_server *server, t_egg *egg)
{
	t_egg *tmp = server->eggs;

	if (egg->id == tmp->id)
		server->eggs = egg->next;
	else {
		while (tmp->next && tmp->next->id != egg->id)
			tmp = tmp->next;
		tmp->next = egg->next;
	}
	free(egg);
}

void remove_all_eggs(t_egg *eggs)
{
	t_egg *egg = eggs;

	while (eggs) {
		egg = eggs->next;
		free(eggs);
		eggs = egg;
	}
}