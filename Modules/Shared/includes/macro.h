
/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** macro
*/

#pragma once

#ifndef _GNU_SOURCE /* default defined on c++ */
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR 84
#define FAILED 1
#define FAILURE 1
#define COMMAND_SIZE_SERVER 7
#define COMMAND_SIZE_AI 4
#define DEFAULT_VALUE -1
#define ERR_FC -1
#define FD_ERROR -1

#define MAX_LEVEL 9
#define INVENT_SIZE 7

#define FCT_FAILED(s) fprintf(stderr, "Error: %s failed.\n", s)
#define NOT_NUMBER(n) fprintf(stderr, "Error: %s must be a valid number.\n", n)

#define USAGE_SERVER "USAGE: ./zappy_server -p port -x width -y \
	height -n name1 name2 ... -c clientsNb -f freq\
	\n\tport\tis the port number\
	\n\twidth\tis the width of the world\
	\n\theight\tis the height of the world\
	\n\tnameX\tis the name of the team X\
	\n\tclientsNb\tis the number of authorized clients per team\
	\n\tfreq\tis the reciprocal of time unit for execution of actions\n"

#define USAGE_AI "USAGE: ./zappy_ai -p port -n name -h machine\
	\n\tport\tis the port number\
	\n\tname\tis the name of the team\
	\n\tmachine\tis the name of the machine; localhost by default\n"

#define LOOK_TIME 7
#define FORWARD_TIME 7
#define RIGHT_TIME 7
#define LEFT_TIME 7
#define BROADCAST_TIME 7
#define INVENTORY_TIME 1
#define LIFE_TIME 126
#define TAKE_TIME 7
#define SET_TIME 7
#define EJECT_TIME 7
#define EGG_TIME 42
#define HATCH_TIME 600
#define INCANTATION_TIME 300

#define SPAWN_FOOD 20
#define SPAWN_LINEMATE 30
#define SPAWN_DERAUMERE 40
#define SPAWN_SIBUR 50
#define SPAWN_MENDIANE 60
#define SPAWN_PHIRAS 70
#define SPAWN_THYSTAME 80

#define START_ELEVATION "Elevation underway"
#define ELEVATION_FAILED "ko"

#define SEND_TEAM "tna %s\n"
#define SEND_CELL "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n"
#define SEND_EGG "enw %ld %ld %d %d\n"
#define SEND_CLIENT "pnw %ld %d %d %ld %ld %s\n"