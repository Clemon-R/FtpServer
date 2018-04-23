/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** server2
*/

#include "server.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

void	close_socket(server_t *server)
{
	client_t	*current;
	client_t	*tmp;

	if (!server)
		return;
	current = server->current;
	while (current != 0){
		tmp = current;
		current = current->next;
		tmp->cdel(tmp);
	}
	if (server->fd != -1)
		close(server->fd);
	if (server->type == HOST)
		free(server->list);
	free(server);
}

int	create_socket(server_t *server, char *root, enum SERVER_TYPE type)
{
	int	opt = 1;

	server->pe = getprotobyname("TCP");
	if (!server->pe)
		return (-1);
	printf("Creating the socket\n");
	server->fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
	if (server->fd == -1)
		return (-1);
	else if (type == HOST && setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR
	, (char *)&opt, sizeof(opt)) == -1)
		return (-1);
	printf("Socket created\n");
	server->type = type;
	if (type == HOST){
		server->list = get_list();
		server->root = root;
	}
	return (server->fd);
}

int	set_port(server_t *server, unsigned int port, const char *ip)
{
	int			result;

	if (!server || server->fd == -1)
		return (1);
	server->s_in.sin_family = AF_INET;
	server->s_in.sin_port = htons(port);
	server->s_in.sin_addr.s_addr = inet_addr(ip);
	printf("Setting the port...\n");
	result = bind(server->fd
	, (struct sockaddr *)&server->s_in, sizeof(server->s_in));
	if (result == -1)
		return (1);
	printf("The port has been set\n");
	return (0);
}

server_t	*init_server(void)
{
	server_t	*server;

	server = malloc(sizeof(server_t));
	if (!server)
		return (0);
	server->cnew = &create_socket;
	server->cdel = &close_socket;
	server->start = &start_server;
	server->set_port = &set_port;
	server->last = 0;
	server->current = 0;
	server->root = 0;
	server->parent = 0;
	return (server);
}