/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** user
*/

#include "commands.h"

void	user(client_t *client, const char *arg)
{
	if (!arg)
		write(client->fd, "530 Permission denied\n", 22);
	client->account.user = strdup(arg);
	write(client->fd, "331 Enter the password\n", 23);
}