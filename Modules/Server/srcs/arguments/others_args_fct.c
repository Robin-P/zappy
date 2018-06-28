/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** others_args_fct
*/

#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "tools.h"
#include "arguments_server.h"

int port(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) <= 0)
		return (NOT_NUMBER("port"), ERROR);
	opt->port = atoi(av[0]);
	return (SUCCESS);
}

int width(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) < 10 || atoi(av[0]) > 30)
		return (NOT_NUMBER("width"), ERROR);
	opt->x = atoi(av[0]);
	return (SUCCESS);
}

int height(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) < 10 || atoi(av[0]) > 30)
		return (NOT_NUMBER("height"), ERROR);
	opt->y = atoi(av[0]);
	return (SUCCESS);
}