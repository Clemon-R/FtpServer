/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** pwd
*/

#include "commands.h"
#include "directory.h"

void	pwd(client_t *client, const char *argv)
{
	char	*path = get_path(client->current);

	write(client->fd, "257 \"/", 6);
	if (path)
		write(client->fd, path, strlen(path));
	write(client->fd, "\"\n", 2);
	free(path);
}