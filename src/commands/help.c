/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** help
*/

#include "commands.h"

void	help(client_t *client, const char *argv)
{
	write(client->fd, "214-The following commands are recognized\n", 42);
	for (int i = 0;i < NBR_COMMANDS;i += 1){
		write(client->fd, " ", 1);
		write(client->fd
			, client->server->list[i].name
			, strlen(client->server->list[i].name));
	}
	write(client->fd, "\n", 1);
	write(client->fd, "214 Help OK\n", 12);
}