/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sockets
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef enum {
	CLIENT,
	SERVER
} e_socket_type;

int create_socket(const int, const in_addr_t, const e_socket_type);
bool is_fd_open(const int);
