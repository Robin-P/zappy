/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** send_commands
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "ai.h"
#include "macro.h"
#include "tools.h"
#include "get_next_line.h"
#include "ai_list.h"

void send_command(t_ai *ai, const char *msg)
{
	dprintf(ai->fd, "%s\n", msg);
	printf("[!] Command : [%s]\n", msg);
	add_in_list(&ai->list, msg);
}

char *readline(const int fd)
{
	return (get_next_line(fd));
}