/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** stor
*/

#include "commands.h"

void	stor(client_t *client, const char *argv)
{
	if (!argv || !*argv || !client->data || !client->data->current)
		return;
	client->data->current->file = strdup(argv);
	write(client->fd, "150 Waiting data...\n", 20);
}