/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai_list
*/

#include "ai_list.h"

void add_in_list(t_request **list, const char *el)
{
	t_request *node = malloc(sizeof(t_request));

	node->msg = strdup(el);
	node->next = *list;
	*list = node;
}

size_t listlen(t_request *list)
{
	size_t len = 0;

	for (t_request *tmp = list; tmp; tmp = tmp->next)
		len++;
	return (len);
}

void delete_list(t_request *list)
{
	t_request *node = list;

	while (list) {
		node = list->next;
		free(list->msg);
		free(list);
		list = node;
	}
}

void delete_node(t_request **list, size_t index)
{
	t_request *tmp = *list;
	t_request *save = NULL;

	if (index >= listlen(*list))
		return;
	if (index == 0) {
		*list = tmp->next;
		free(tmp->msg);
		free(tmp);
		return;
	}
	for (size_t i = 0; i < index - 1; i++)
		tmp = tmp->next;
	save = tmp->next;
	tmp->next = save->next;
	free(save->msg);
	free(save);
}

char *get_nth_data(t_request *list, size_t n)
{
	size_t count = 0;
	t_request *tmp = NULL;

	if (n > listlen(list) || !list)
		return (NULL);
	for (tmp = list; tmp && count < n; tmp = tmp->next)
		count++;
	return (tmp->msg);
}