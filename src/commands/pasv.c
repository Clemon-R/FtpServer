/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** pasv
*/

#include "commands.h"
#include "server.h"
#include <netinet/in.h>
#include <arpa/inet.h>

static void	set_msg(char *buff, client_t *client)
{
	char	*ip;
	unsigned int	port = ntohs(client->data->s_in.sin_port);

	ip = inet_ntoa(client->server->s_in.sin_addr);
	sprintf(buff, "227 Entering Passive Mode (%s,%d,%d)\n"
		, ip, port / 256, port % 256);
	for (int i = 0;buff[i];i++)
		if (buff[i] == '.')
			buff[i] = ',';
}

static void	set_server(server_t *server, client_t *client)
{
	int		result = 1;
	unsigned int	port = 1023;

	server->cnew(server, 0, DATA);
	while (result){
		port += 1;
		if (ntohs(client->server->s_in.sin_port) != port)
			result = server->set_port(server
					, port
					, "0.0.0.0");
	}
	server->start(server);
}

void	pasv(client_t *client, const char *argv)
{
	server_t	*server;
	char		buff[1024];

	if (client->data)
		client->data->cdel(client->data);
	client->data = 0;
	server = init_server();
	if (!server){
		write(client->fd, "550 Permission denied\n", 22);
		return;
	}
	set_server(server, client);
	client->data = server;
	server->parent = client;
	set_msg(buff, client);
	write(client->fd, buff, strlen(buff));
}