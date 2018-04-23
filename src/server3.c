/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** server3
*/

#include "server.h"
int	start_server(server_t *server)
{
	int	result;
	fd_set			readfts;

	printf("Trying to start the server\n");
	if (!server || server->fd == -1)
		return (1);
	result = listen(server->fd, 100);
	if (result == -1)
		return (1);
	if (server->type == DATA)
		return (0);
	printf("Server running...\n");
	while (1){
		set_fdset(server, &readfts);
		select(get_the_highest_fd(server) + 1, &readfts, 0, 0, 0);
		if (FD_ISSET(server->fd, &readfts))
			handle_main(server);
		handle_packet_s(server, &readfts);
	}
	return (0);
}