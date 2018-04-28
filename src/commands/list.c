/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** list
*/

#include "commands.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>

static char	*root_path(client_t *client)
{
	int	root_len = strlen(client->server->root);
	char	*current = get_path(client->current);
	int	current_len = (current ? strlen(current) : 0);
	char	*new = malloc(sizeof(char) *
	(root_len + current_len + 2));

	if (!new)
		return (0);
	strcpy(new, client->server->root);
	if (current){
		strcat(new, "/");
		strcat(new, current);
	}
	if (current)
		free(current);
	return (new);
}

static char	send_data(client_t *client, const char *root)
{
	FILE	*fd;
	char	*buff = 0;
	size_t	size = 0;
	char	*path = malloc(sizeof(char) * (strlen(root) + 7));
	char	first = 1;

	strcpy(path, "ls -l ");
	strcat(path, root);
	fd = popen(path, "r");
	free(path);
	if (!fd)
		return (0);
	write(client->fd, "150 Here comes the directory listing.\n", 38);
	while (getline(&buff, &size, fd) != -1){
		if (!first)
			write(client->data->current->fd, buff, strlen(buff));
		first = 0;
	}
	pclose(fd);
	return (1);
}

void	list(client_t *client, const char *argv)
{
	char	*root = root_path(client);

	if (!client->data || !client->data->current){
		write(client->fd, "425 Impossible to list files\n", 29);
		return;
	}
	if (!root || !send_data(client, root)){
		free(root);
		write(client->fd, "550 Impossible to list files\n", 29);
		return;
	}
	write(client->fd, "250 Directory send OK.\n", 23);
	free(root);
	client->data->cdel(client->data);
	client->data = 0;
}