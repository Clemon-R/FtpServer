/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** client
*/

#include "client.h"
#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

static void	init_account(client_t *client)
{
	client->account.user = 0;
	client->account.logged = 0;
}

static int	create_client(client_t *client, int fd
				, struct sockaddr_in *socket)
{
	char	*welcome = "220 Good connection\n";
	if (!client || fd == -1)
		return (1);
	client->fd = fd;
	client->current = 0;
	client->s_in = socket;
	client->data = 0;
	if (client->server->type == HOST)
		write(fd, welcome, strlen(welcome));
}

static void	close_client(client_t *client)
{
	if (!client)
		return;
	printf("Close client %d\n", client->fd);
	if (client->fd != -1)
		close(client->fd);
	if (client->prev)
		client->prev->next = client->next;
	if (client->next)
		client->next->prev = client->prev;
	if (client == client->server->current)
		client->server->current = client->next;
	if (client == client->server->last)
		client->server->last = client->prev;
	if (client->current)
		delete_paths(client->current);
	if (client->data)
		client->data->cdel(client->data);
	free(client);
}

static void	handle_packet_c(client_t *client)
{
	char	buff[1025];
	int	len;

	len = read(client->fd, &buff, 1024);
	if (len == 0){
		client->cdel(client);
		return;
	}
	buff[len - 1] = 0;
	for (int i = 0;buff[i];i += 1)
		if (buff[i] == '\n' || buff[i] == '\r')
			buff[i] = 0;
	printf("Packet: %s\n", buff);
	handle_command(client->server, client, buff);
}

client_t	*init_client(server_t *server, client_t *last)
{
	client_t	*client;

	client = malloc(sizeof(client_t));
	if (!client)
		return (0);
	client->cnew = &create_client;
	client->cdel = &close_client;
	client->handle_packet = &handle_packet_c;
	client->prev = last;
	client->next = 0;
	client->server = server;
	init_account(client);
	if (last)
		last->next = client;
	return (client);
}

void	reception_file(client_t *client)
{
	char	buff[1025];
	int	len;
	int	fd;
	char	*msg = "226 File transfered\n";

	len = read(client->fd, &buff, 1024);
	if (len == 0){
		write(client->server->parent->fd, msg, strlen(msg));
		client->server->parent->data = 0;
		client->server->cdel(client->server);
		return;
	}
	buff[len] = 0;
	fd = open(client->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return;
	write(fd, buff, len);
	close(fd);
}