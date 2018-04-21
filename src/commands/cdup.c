/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** cdup
*/

#include "commands.h"

void	cdup(client_t *client, const char *argv)
{
	char	*msg = "250 Path successfully changed\n";
	client->current = 0;
	write(client->fd, msg, strlen(msg));
}