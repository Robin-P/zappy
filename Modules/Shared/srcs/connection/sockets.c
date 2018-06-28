/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sockets
*/

#include <fcntl.h>
#include "macro.h"
#include "sockets.h"

static int safe_close(const int fd, const int ret)
{
	if (close(fd) == -1)
		return (FCT_FAILED("close"), ERROR);
	return (ret);
}

static int client(int fd, struct sockaddr_in *s_in)
{
	if (bind(fd, (const struct sockaddr *)s_in, sizeof(*s_in)) == -1) {
		FCT_FAILED("bind");
		return (safe_close(fd, FD_ERROR));
	}
	if (listen(fd, 42) == -1)
		return (FCT_FAILED("listen"), safe_close(fd, FD_ERROR));
	return (fd);
}

static int server(int fd, struct sockaddr_in *s_in)
{
	if (connect(fd, (struct sockaddr *)s_in, sizeof(*s_in)) == -1)
		return (FCT_FAILED("connect"), safe_close(fd, FD_ERROR));
	return (fd);
}

bool is_fd_open(const int fd)
{
	return (fcntl(fd, F_GETFD) != -1);
}

int create_socket(const int port, const in_addr_t addr,
			const e_socket_type socket_type)
{
	int i = 1;
	int fd;
	struct protoent *pe;
	struct sockaddr_in s_in;

	pe = getprotobyname("TCP");
	if (!pe)
		return (FCT_FAILED("getprotobyname"), FD_ERROR);
	fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &i,
		sizeof(int)) < 0)
		return (FCT_FAILED("setsockopt"), FD_ERROR);
	if (fd == -1)
		return (FCT_FAILED("socket"), FD_ERROR);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = addr;
	return (socket_type == SERVER ? client(fd, &s_in) : server(fd, &s_in));
}