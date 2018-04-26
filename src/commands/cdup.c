/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** cdup
*/

#include "commands.h"

void	cdup(client_t *client, const char *argv)
{
	path_t	*tmp = client->current;

	if (client->current){
		client->current = client->current->parent;
		delete_path(tmp);
	}
	char	*msg = "250 Path successfully changed\n";
	write(client->fd, msg, strlen(msg));
}