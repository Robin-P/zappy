/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** begin_connection
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "macro.h"
#include "ai.h"

static int try_connect(char *buf)
{
	int left_client = atoi(buf);

	if (left_client <= 0)
		return (fprintf(stderr, "Can't connect: too many clients.\n"), ERROR);
	return (SUCCESS);
}

static int receipt_infos(t_ai *ai)
{
	char **tmp = NULL;
	char *buf = readline(ai->fd);

	if (buf) {
		if (try_connect(buf) == ERROR)
			return (free(buf), ERROR);
		free(buf);
		buf = readline(ai->fd);
		if (!buf)
			return (ERROR);
		tmp = str_to_tab(buf, " ");
		ai->opts->dim.x = atoi(tmp[0]);
		ai->opts->dim.y = atoi(tmp[1]);
		return (free_tab(tmp), free(buf), SUCCESS);
	}
	return (ERROR);
}

int receipt_welcome(t_ai *ai)
{
	char *buf = readline(ai->fd);

	if (buf) {
		printf("%s\n", buf);
		free(buf);
		send_command(ai, ai->opts->name);
		delete_node(&ai->list, 0);
		return (receipt_infos(ai));
	}
	return (ERROR);
}