/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_response
*/

#include "ai.h"
#include "macro.h"

int look_around(t_ai *ai, char *s)
{
	char **tab = get_data_from_look(s);
	int dir = rand() % 2;

	printf("RES : %s\n", s);
	if (!tab)
		return (FAILURE);
	ai->inv[EL_PLAYER] = count_substr(tab[0], "player");
	if (strcmp(tab[0], "player") == 0)
		ai->state = dir == 0 ? AI_MOVE : AI_TURN;
	else
		ai->state = AI_TAKE;
	free_tab(tab);
	if (ai->look)
		free(ai->look);
	ai->look = strdup(s);
	return (SUCCESS);
}

int pass(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	printf("RES : %s\n", s);
	return (SUCCESS);
}

int broadcast(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	printf("RES : %s\n", s);
	return (SUCCESS);
}

int forward(t_ai *ai, char *s)
{
	char **tab = NULL;
	char **tmp = NULL;

	printf("RES : %s\n", s);
	if (strcmp(s, "ko") == 0 && !ai->look)
		return (ERROR);
	tab = get_data_from_look(ai->look);
	tmp = str_to_tab(tab[0], " ");
	for (int i = 0; tmp[i] && strcmp(tmp[i], "player") == 0; i++)
	if (!tmp[i])
		return (free_tab(tab), free_tab(tmp), ERROR);
	ai->state = AI_TAKE;
	free_tab(tmp);
	return (SUCCESS);
}

int turn(t_ai *ai, char *s)
{
	printf("RES : %s\n", s);

	if (strcmp(s, "KO") == 0)
		return (ERROR);
	ai->state = AI_MOVE;
	return (SUCCESS);
}