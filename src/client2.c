/*
** EPITECH PROJECT, 2018
** ft
** File description:
** client2
*/

#include "client.h"
#include <fcntl.h>

static void	end_transit(client_t *client)
{
	write(client->server->parent->fd
	, client->server->fd == client->fd ? "250" : "226", 3);
	write(client->server->parent->fd
	, " File transfered\n", 17);
	client->server->parent->data = 0;
	client->server->cdel(client->server);	
}

void	reception_file(client_t *client)
{
	char	buff[1025];
	int	len = 1;
	int	fd = open(client->file, O_WRONLY | O_APPEND | O_CREAT, 0644);

	if (fd == -1){
		write(client->server->parent->fd, "250 Error file\n", 15);
		return;
	}
	while (len){
		len = read(client->fd, &buff, 1024);
		if (len == 0){
			end_transit(client);
			break;
		}
		buff[len] = 0;
		write(fd, buff, len);
	}
	close(fd);
}