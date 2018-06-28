/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** parser
*/

#include "player_actions.h"
#include "manage_time.h"

char *forward(t_server *server, t_message *cmd)
{
	char *str;

	cmd->finish_date = time_until_finish(FORWARD_TIME, server->opts->freq);
	switch (cmd->owner->look) {
		case 0: (cmd->owner->pos.y = ((cmd->owner->pos.y
		<= 0 ? server->opts->y : cmd->owner->pos.y) - 1));
		break;
		case 1: (cmd->owner->pos.x = ((cmd->owner->pos.x
		>= server->opts->x - 1 ? -1 : cmd->owner->pos.x) + 1));
		break;
		case 2: (cmd->owner->pos.y = ((cmd->owner->pos.y
		>= server->opts->y - 1 ? -1 : cmd->owner->pos.y) + 1));
		break;
		case 3: (cmd->owner->pos.x = ((cmd->owner->pos.x
		<= 0 ? server->opts->x : cmd->owner->pos.x) - 1));
		default: break;}
	asprintf(&server->messages->graphics_message, "ppo %li %i %i %li",
			cmd->owner->player_id, cmd->owner->pos.x,
			cmd->owner->pos.y, cmd->owner->look + 1);
	return (asprintf(&str, "ok"), str);
}

char *right(t_server *server, t_message *cmd)
{
	char *str;

	cmd->finish_date = time_until_finish(RIGHT_TIME, server->opts->freq);
	cmd->owner->look += (cmd->owner->look >= 3 ? -3 : 1);
	asprintf(&server->messages->graphics_message, "ppo %li %i %i %li",
			cmd->owner->player_id, cmd->owner->pos.x,
			cmd->owner->pos.y, cmd->owner->look + 1);
	return (asprintf(&str, "ok"), str);
}

char *left(t_server *server, t_message *cmd)
{
	char *str;

	cmd->finish_date = time_until_finish(LEFT_TIME, server->opts->freq);
	cmd->owner->look -= (cmd->owner->look <= 0 ? -3 : 1);
	asprintf(&server->messages->graphics_message, "ppo %li %i %i %li",
			cmd->owner->player_id, cmd->owner->pos.x,
			cmd->owner->pos.y, cmd->owner->look + 1);
	return (asprintf(&str, "ok"), str);
}
