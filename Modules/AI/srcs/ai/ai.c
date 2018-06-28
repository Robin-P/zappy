/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ai.h"
#include "macro.h"
#include "commands.h"
#include "tools.h"

char **get_data_from_look(const char *str)
{
	char **tab = NULL;
	char *tmp = NULL;
	char *tmp2 = NULL;

	if (!str)
		return (NULL);
	tmp = strdup(str);
	if (!tmp)
		return (NULL);
	tmp2 = replace(tmp, ",,", ", ,");
	tab = str_to_tab((char *)tmp, ",");
	if (!tab)
		return (NULL);
	for (int i = 0; tab[i]; i++) {
		tab[i] = lstrip_m(tab[i], "[ ");
		tab[i] = rstrip_m(tab[i], "] ");
	}
	free(tmp);
	free(tmp2);
	return (tab);
}

static int take_object(char **cmd, t_ai *ai)
{
	static const char *objects[] = {"linemate", "deraumere", "sibur",
		"mendiane", "phiras", "thystame", "food", NULL};
	char **tab = str_to_tab(cmd[0], " ");
	char msg[100];
	char *t;

	for (int i = 0; tab[i]; i++) {
		for (int j = 0; objects[j]; j++) {
			if (strcmp(tab[i], objects[j]) == 0) {
				sprintf(msg, "Take %s", tab[i]);
				send_command(ai, msg);
				t = readline(ai->fd);
				printf("%s\n", t);
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS);
}

int look_for_ressources(t_ai *ai, const char *tmp)
{
	char **tab = get_data_from_look(tmp);
	bool no_res = true;
	int random_dir = rand() % 2;
	char t[4096];

	if (strcmp(tab[0], "") != 0)
		return (take_object(tab, ai));
	if (no_res == false) {
		send_command(ai, random_dir == 0 ? TURN_LEFT : TURN_RIGHT);
		read(ai->fd, t, 4096);
	}
	return (SUCCESS);
}

void delete_ai(t_ai *ai)
{
	delete_list(ai->list);
	free(ai->look);
	close(ai->fd);
}

int run_ai(t_ai *ai)
{
	t_associate_state arr[] = {
		{AI_LOOK, look_cmd},
		{AI_TAKE, take_cmd},
		{AI_MOVE, move_cmd},
		{AI_INCANT, incant_cmd},
		{AI_TURN, turn_cmd}
	};

	ai->state = AI_LOOK;
	if (receipt_welcome(ai))
		return (ERROR);
	while (ai->run) {
		usleep(rand() % 5000 + 1000);
		if (listlen(ai->list) < 10)
			for (int i = 0; i < 5; i++)
				if (ai->state == arr[i].state)
					arr[i].fct(ai);
		wait_for_response(ai);
	}
	delete_ai(ai);
	return (SUCCESS);
}
