/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** dele
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

static char	*get_file_name(const char *path, const char *file)
{
	char	*filename;


	if (!path || !file || !*file)
		return (0);
	filename = malloc(sizeof(char) * (strlen(path) + strlen(file) + 2));
	if (!filename)
		return (0);
	strcpy(filename, path);
	strcat(filename, "/");
	strcat(filename, file);
	return (filename);
}

void	dele(client_t *client, const char *argv)
{
	int	fd;
	char	*path;
	char	*filename;

	path = root_path(client);
	filename = get_file_name(path, argv);
	if (path)
		free(path);
	if (!path || !filename){
		write(client->fd, "550 Permission denied\n", 22);
		return;
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1 || close(fd) == -1 || remove(filename) == -1)
		write(client->fd, "550 Permission denied\n", 22);
	else
		write(client->fd, "250 File deleted\n", 17);
	free(filename);
}