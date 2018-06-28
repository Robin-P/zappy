/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai_list
*/

#pragma once

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_request {
	char *msg;
	struct s_request *next;
} t_request;

void add_in_list(t_request **, const char *);
void dump_list(t_request *);
void delete_node(t_request **, size_t);
void delete_list(t_request *);
size_t listlen(t_request *);
char *get_nth_data(t_request *, size_t);