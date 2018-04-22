/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** server
*/

#include "server.h"
#include "client.h"

void	handle_client(server_t *server, int client_fd
			, struct sockaddr_in *socket)
{
	client_t	*client;

	client = init_client(server, server->last);
	if (!client)
		return;
	else if (!server->current)
		server->current = client;
	server->last = client;
	client->cnew(client, client_fd, socket);
}

int	get_the_highest_fd(server_t *server)
{
	int	result = server->fd;
	client_t	*current = server->current;

	while (current != 0){
		if (current->fd > result)
			result = current->fd;
		if (current->data && current->data->fd > result)
			result = current->data->fd;
		current = current->next;
	}
	return (result);
}

void	set_fdset(server_t *server, fd_set *readfts)
{
	client_t	*current = server->current;

	FD_ZERO(readfts);
	FD_SET(server->fd, readfts);
	while (current != 0){
		printf("Adding %d\n", current->fd);
		FD_SET(current->fd, readfts);
		if (current->data)
			FD_SET(current->data->fd, readfts);
		current = current->next;
	}
}

void	handle_main(server_t *server)
{
	int	client_fd = 0;
	struct sockaddr_in	s_client_in;
	socklen_t		s_client_size = sizeof(s_client_in);

	client_fd = accept(server->fd
	, (struct sockaddr *)&s_client_in, &s_client_size);
	if (client_fd == -1)
		return;
	printf("New client\n");
	handle_client(server, client_fd, &s_client_in);
}

void	handle_packet_s(server_t *server, fd_set *readfts)
{
	client_t	*current = server->current;
	client_t	*next;

	while (current != 0){
		next = current->next;
		if (current->data && !current->data->current
		&& FD_ISSET(current->data->fd, readfts))
			handle_main(current->data);
		else if (current->data && current->data->current
		&& FD_ISSET(current->data->fd, readfts))
			reception_file(current->data->current);
		if (FD_ISSET(current->fd, readfts)){
			printf("Client %d\n", current->fd);
			current->handle_packet(current);
		}
		current = next;
	}
}