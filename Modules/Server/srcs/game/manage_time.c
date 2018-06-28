/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_time
*/

#include <sys/time.h>
#include <stdbool.h>

long long time_until_finish(int nb_cycles, int frequence)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000000ll + tv.tv_usec + (long long)(
		((float)nb_cycles / (float)frequence) * 1000000ll));
}

bool is_finish(long long finish_date)
{
	struct timeval tv;

	if (finish_date == -1)
		return (false);
	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000000ll + tv.tv_usec >= finish_date);
}