/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** pass
*/

#include "commands.h"

void	pass(client_t *client, const char *arg)
{
	if (!arg)
		write(client->fd, "530 Permission denied\n", 22);
	else if (!client->account.user)
		write(client->fd, "503 Log in USER first\n", 22);
	else if (client->account.user
	&& strcmp(client->account.user, USER) == 0
	&& (PASS == "" || strcmp(arg, PASS) == 0)){
		client->account.logged = 1;
		write(client->fd, "230 Login successful\n", 21);
	}
	else
		write(client->fd, "530 Login incorrect\n", 20);
}