/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** state_ai
*/

#include "ai.h"
#include "macro.h"
#include "commands.h"

int look_cmd(t_ai *ai)
{
	send_command(ai, LOOK);
	return (SUCCESS);
}

int take_cmd(t_ai *ai)
{
	char **tab = NULL;
	char **tmp = NULL;
	char cmd[256];
	int i;

	if (!ai->look)
		return (ERROR);
	tab = get_data_from_look(ai->look);
	if (!tab)
		return (ERROR);
	tmp = str_to_tab(tab[0], " ");
	if (!tmp)
		return (ERROR);
	for (i = 0; tmp[i] && strcmp(tmp[i], "player") == 0; i++);
	if (tmp[i] != NULL) {
		sprintf(cmd, "Take %s", tmp[i]);
		send_command(ai, cmd);
	}
	return (free_tab(tab), free_tab(tmp), ai->state = AI_LOOK, SUCCESS);
}

int move_cmd(t_ai *ai)
{
	send_command(ai, FORWARD);
	return (SUCCESS);
}

int incant_cmd(t_ai *ai)
{
	send_command(ai, START_INCANTATION);
	return (SUCCESS);
}

int turn_cmd(t_ai *ai)
{
	int dir = rand() % 2;

	send_command(ai, dir == 0 ? "Turn right" : "Turn left");
	return (SUCCESS);
}