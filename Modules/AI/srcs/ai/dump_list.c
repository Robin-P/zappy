/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** dump_list
*/

#include "ai_list.h"

void dump_list(t_request *list)
{
	for (t_request *tmp = list; tmp; tmp = tmp->next)
		printf("%s\n", tmp->msg);
}