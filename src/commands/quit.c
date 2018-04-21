/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** quit
*/

#include "commands.h"

void	quit(client_t *client, const char *arg)
{
	char	*msg = "221 Bye bye !\n";

	write(client->fd, msg, strlen(msg));
	client->cdel(client);
}