/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** list
*/

#include "commands.h"

void	list(client_t *client, const char *argv)
{
	if (!client->data || !client->data->current){
		write(client->fd, "550 Use PORT or PASV before\n", 28);
		return;
	}
	write(client->fd, "OK\n", 3);
	write(client->data->current->fd, "test\n", 5);
	client->data->cdel(client->data);
	client->data = 0;
}