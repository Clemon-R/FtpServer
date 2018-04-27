/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** stor
*/

#include "commands.h"
#include <fcntl.h>

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

void	stor(client_t *client, const char *argv)
{
	int	fd;
	char	*root = root_path(client);
	char	*file;

	if (!root || !argv || !*argv 
	|| !client->data || !client->data->current){
		write(client->fd, "550 Impossible to transfert\n", 28);
		return;
	}
	file = malloc(sizeof(char) * (strlen(root) + strlen(argv) + 2));
	if (!file){
		write(client->fd, "550 Impossible to transfert\n", 28);
		return;
	}
	strcat(file, root);
	strcpy(file, "/");
	strcpy(file, argv);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd != -1){
		write(client->fd, "550 File already exist\n", 23);
		close(fd);
		return;
	}
	client->data->current->file = strdup(argv);
	write(client->fd, "150 Waiting data...\n", 20);
}