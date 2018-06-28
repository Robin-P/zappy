/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** arguments
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arguments_ai.h"
#include "macro.h"
#include "ai.h"

bool check_commands(t_opts_ai *opt)
{
	return (!(opt->port <= 0 || !opt->name || !opt->machine));
}

static t_args *populate_args(void)
{
	t_args *args = malloc(sizeof(t_args) * (COMMAND_SIZE_AI + 1));

	if (!args)
		return (FCT_FAILED("malloc"), NULL);
	args[0] = (t_args){"-p", &port};
	args[1] = (t_args){"-n", &name};
	args[2] = (t_args){"-h", &machine};
	args[3] = (t_args){"-help", &help};
	args[4] = (t_args){NULL};
	return (args);
}

static void populate_options(t_opts_ai *opt)
{
	opt->port = DEFAULT_VALUE;
	opt->name = NULL;
	opt->machine = NULL;
}

static int check_cmd(char **av, t_args *args, t_opts_ai *opt, t_vec2d *vec)
{
	if (strcmp(av[vec->x], args[vec->y].flag) == 0 &&
		args[vec->y].function(&av[vec->x + 1], opt) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int manage_commands(char **av, t_opts_ai *opt)
{
	t_args *args = populate_args();
	t_vec2d vec;

	populate_options(opt);
	if (!args)
		return (ERROR);
	for (vec.x = 1; av[vec.x]; vec.x++)
		for (vec.y = 0; vec.y < COMMAND_SIZE_AI; vec.y++)
			if (check_cmd(av, args, opt, &vec) == ERROR)
				return (free(args), ERROR);
	free(args);
	return (SUCCESS);
}