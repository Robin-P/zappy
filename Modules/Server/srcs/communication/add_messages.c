/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** add_messages
*/

#include "communication.h"

static void push_back_message(t_server *server, t_message *message)
{
	t_message *tmp = server->messages;

	if (server->messages) {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = message;
	}
	else
		server->messages = message;
}

int add_message_in_list(t_server *server, t_client *client,
			const char *request)
{
	static size_t id = 0;
	t_message *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	new->owner = client;
	new->request = strdup(request);
	if (!new->request)
		return (FCT_FAILED("strdup"), ERROR);
	new->response = NULL;
	new->id = id++;
	new->finish_date = DEFAULT_VALUE;
	new->graphics_message = NULL;
	new->next = NULL;
	push_back_message(server, new);
	return (SUCCESS);
}

int add_special_response(t_server *server, t_client *client, char *response)
{
	t_message *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	new->owner = client;
	new->request = NULL;
	new->graphics_message = NULL;
	new->response = response;
	new->finish_date = 0;
	new->next = server->messages;
	server->messages = new;
	return (SUCCESS);
}
