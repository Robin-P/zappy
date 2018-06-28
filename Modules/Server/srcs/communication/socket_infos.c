/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** socket_infos
*/

#include "communication.h"
#include "client.h"

static int get_max_fd(t_server *server)
{
	int max = server->socket;
	t_client *tmp = server->clients;
	t_graphical_client *tmp_g = server->graphical_client;

	while (tmp) {
		max = (tmp->socket > max ? tmp->socket : max);
		tmp = tmp->next;
	}
	while (tmp_g) {
		max = (tmp_g->socket > max ? tmp_g->socket : max);
		tmp_g = tmp_g->next;
	}
	return (max);
}

static void reset_all_sockets(t_server *server, fd_set *fd_read)
{
	t_client *tmp = server->clients;
	t_graphical_client *tmp_g = server->graphical_client;

	FD_ZERO(fd_read);
	FD_SET(server->socket, fd_read);
	while (tmp) {
		FD_SET(tmp->socket, fd_read);
		tmp = tmp->next;
	}
	while (tmp_g) {
		FD_SET(tmp_g->socket, fd_read);
		tmp_g = tmp_g->next;
	}
}

static int read_on_client(t_server *srv, t_client *cli)
{
	static char buffer[4096];
	int size;

	size = read(cli->socket, buffer, 4096);
	buffer[size] = '\0';
	for (char *tmp = strtok(buffer, "\n") ; tmp &&
	cli->request_number < 10 ; tmp = strtok(NULL, "\n")) {
		if (strcmp(tmp, "GRAPHIC") == 0)
			return (is_graphical(srv, cli), ERROR);
		if (!cli->team)
			find_team(srv, cli, tmp);
		else if (add_message_in_list(srv,
			cli, tmp) == ERROR)
			return (ERROR);
		else
			cli->request_number += 1;
	}
	return (size > 0 ? SUCCESS : (remove_client(srv, cli, true), ERROR));
}

static int are_clients_written(t_server *server, fd_set *fd_read)
{
	t_client *tmp = server->clients;
	t_graphical_client *client_g = server->graphical_client;

	while (client_g) {
		if (FD_ISSET(client_g->socket, fd_read)) {
			fprintf(stderr, "Client graphic ecris\n");
			client_g = (read_on_client_g(server, client_g) == ERROR
				? server->graphical_client : client_g->next);
		} else
			client_g = client_g->next;
	}
	while (tmp) {
		if (FD_ISSET(tmp->socket, fd_read))
			tmp = (read_on_client(server, tmp) == ERROR ?
			server->clients : tmp->next);
		else
			tmp = tmp->next;
	}
	return (SUCCESS);
}

int manage_sockets(t_server *server)
{
	static fd_set fd_read;
	struct timeval tv = {0, 50};

	reset_all_sockets(server, &fd_read);
	if (select(get_max_fd(server) + 1, &fd_read, NULL, NULL, &tv) == -1)
		return (FCT_FAILED("select"), ERROR);
	if (FD_ISSET(server->socket, &fd_read) && add_client(server) == ERROR)
		return (ERROR);
	return (are_clients_written(server, &fd_read));
}