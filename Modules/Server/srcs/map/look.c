/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include "macro.h"
#include "server.h"
#include "manage_time.h"

char *look_top(t_server *server, char *str, t_pos pos, t_message *cmd)
{
	for (int i = 0; i < (int)(1 + cmd->owner->level); ++i) {
		if (pos.y - i < 0)
			pos.y += server->opts->y;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_top_bot(server, str,
			(t_pos){j - 2 * i / 2 + pos.x, -i + pos.y}, cmd);
		}
	}
	return (str);
}

char *look_right(t_server *server, char *str, t_pos pos, t_message *cmd)
{
	for (int i = 0; i < (int)(1 + cmd->owner->level); ++i) {
		if (i + pos.x >= server->opts->x)
			pos.x -= server->opts->x;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_left_right(server, str,
			(t_pos){i + pos.x, j - 2 * i / 2 + pos.y}, cmd);
		}
	}
	return (str);
}

char *look_bot(t_server *server, char *str, t_pos pos, t_message *cmd)
{
	for (int i = 0; i < (int)(1 + cmd->owner->level); ++i) {
		if (i + pos.y >= server->opts->y)
			pos.y -= server->opts->y;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_top_bot(server, str,
			(t_pos){j - 2 * i / 2 + pos.x, i + pos.y}, cmd);
		}
	}
	return (str);
}

char *look_left(t_server *server, char *str, t_pos pos, t_message *cmd)
{
	for (int i = 0; i < (int)(1 + cmd->owner->level); ++i) {
		if (pos.x - i < 0)
			pos.x += server->opts->x;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_left_right(server, str,
			(t_pos){-i + pos.x, j - 2 * i / 2 + pos.y}, cmd);
		}
	}
	return (str);
}

static char *(*fct[])(t_server *, char *, t_pos pos, t_message *cmd) = {
	look_top,
	look_right,
	look_bot,
	look_left
};

char *look(t_server *server, t_message *cmd)
{
	char *str;
	t_pos pos = {cmd->owner->pos.x, cmd->owner->pos.y};
	int direction = cmd->owner->look;

	cmd->finish_date = time_until_finish(LOOK_TIME, server->opts->freq);
	asprintf(&str, "[");
	str = (*fct[direction])(server, str, pos, cmd);
	return (mallocat(str, " ]", ""));
}
