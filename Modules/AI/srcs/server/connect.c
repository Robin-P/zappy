/*
** EPITECH PROJECT, 2018
** server_zappy ()
** File description:
** connect
*/

#include <sys/time.h>
#include <stdio.h>
#include "macro.h"
#include "arguments_ai.h"
#include "sockets.h"
#include "connect_client.h"
#include "ai.h"
#include "tools.h"

static int read_socket(t_ai *ai)
{
	static char buffer[4096];
	int size;
	char *tmp = NULL;

	size = read(ai->fd, buffer, 4096);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp) {
			printf("RESPONSE: %s\n", tmp);
			look_for_ressources(ai, tmp);
			tmp = strtok(NULL, "\n");
		}
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int manage_sockets(t_ai *ai)
{
	static fd_set fd_read;
	struct timeval tv = {0, 50};

	FD_ZERO(&fd_read);
	FD_SET(ai->fd, &fd_read);
	if (select(ai->fd + 1, &fd_read, NULL, NULL, &tv) == -1)
		return (FCT_FAILED("select"), ERROR);
	if (FD_ISSET(ai->fd, &fd_read))
		return (read_socket(ai));
	return (SUCCESS);

}

static void init_ai(t_ai *ai, const int fd, t_opts_ai *opt)
{
	ai->fd = fd;
	ai->level = 0;
	ai->opts = opt;
	for (int i = 0; i < INVENT_SIZE; i++)
		ai->inv[i] = 0;
	ai->list = NULL;
	ai->look = NULL;
	ai->run = true;
}

int connect_to_server(t_opts_ai *opt)
{
	t_ai ai;
	int fd = create_socket(opt->port, inet_addr("127.0.0.1"), CLIENT);

	if (fd == FD_ERROR)
		return (FCT_FAILED("create_socket"), ERROR);
	init_ai(&ai, fd, opt);
	return (run_ai(&ai));
}