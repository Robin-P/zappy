/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** response
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "ai.h"
#include "macro.h"
#include "commands.h"

static int process_response(t_ai *ai, char *str)
{
	static const t_response response[] = {{"Look", look_around},
		{"Inventory", inventory}, {"Turn", turn}, {"Take", pass},
		{"Broadcast", broadcast}, {"Forward", forward},	{NULL}};
	char *data = get_nth_data(ai->list, listlen(ai->list) - 1);

	if (strcmp(str, "dead") == 0)
		return (ai->run = false, SUCCESS);
	if (!data)
		return (ERROR);
	for (int i = 0; response[i].msg; i++) {
		if (strncmp(data, response[i].msg, strlen(response[i].msg)) == 0) {
			response[i].fct(ai, str);
			printf("[!] Delete command\n");
			delete_node(&ai->list, listlen(ai->list) - 1);
			break;
		}
	}
	return (SUCCESS);
}

static int check_response_serv(t_ai *ai)
{
	static char buf[4096];
	int size = read(ai->fd, buf, 4096);
	char **tab = NULL;

	if (size == ERR_FC)
		return (ERROR);
	buf[size] = '\0';
	tab = str_to_tab(buf, "\n");
	if (!tab)
		return (ERROR);
	for (int i = 0; tab[i]; i++)
		process_response(ai, tab[i]);
	free_tab(tab);
	return (SUCCESS);
}

int wait_for_response(t_ai *ai)
{
	static fd_set fd_read;
	struct timeval tv = {0, 50};

	FD_ZERO(&fd_read);
	FD_SET(ai->fd, &fd_read);
	if (select(ai->fd + 1, &fd_read, NULL, NULL, &tv) == -1)
		return (FCT_FAILED("select"), ERROR);
	if (FD_ISSET(ai->fd, &fd_read))
		return (check_response_serv(ai));
	return (SUCCESS);
}