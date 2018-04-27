/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** noop
*/

#include "commands.h"

void	noop(client_t *client, const char *argv)
{
	char	*msg = "200 Rien\n";

	write(client->fd, "200 Rien\n", 9);
}