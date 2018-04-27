/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** quit
*/

#include "commands.h"

void	quit(client_t *client, const char *arg)
{
	write(client->fd, "221 Bye bye !\n", 14);
	client->cdel(client);
}