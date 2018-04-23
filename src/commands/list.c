/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** list
*/

#include "commands.h"
#include <dirent.h>

static char	*root_path(client_t *client)
{
	int	root_len = strlen(client->server->root);
	char	*current = get_path(client->current);
	int	current_len = (current ? strlen(current) : 0);
	char	*new = malloc(sizeof(char) *
	(root_len + current_len + 2));

	strcpy(new, client->server->root);
	if (current){
		strcat(new, "/");
		strcat(new, current);
	}
	if (current)
		free(current);
	return (new);
}

void	list(client_t *client, const char *argv)
{
	char	*root = root_path(client);
	DIR	*rep;
	struct dirent	*file;

	if (!root || !client->data || !client->data->current){
		write(client->fd, "550 Impossible to list file(s)\n", 28);
		return;
	}
	rep = opendir(root);
	if (!rep){
		write(client->fd, "550 Impossible to list file(s)\n", 28);
		return;
	}
	file = readdir(rep);
	write(client->fd, "150 Here comes the directory listing.\n", 39);
	while (file){
		if (file->d_name[0] != '.'){
			write(client->data->current->fd, file->d_name
			, strlen(file->d_name));
			write(client->data->current->fd, "\n", 1);
		}
		file = readdir(rep);
	}
	closedir(rep);
	free(root);
	client->data->cdel(client->data);
	client->data = 0;
	write(client->fd, "226 Directory send OK.\n", 23);
}