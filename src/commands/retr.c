/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** retr
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

static void	send_data(client_t *client, int fd)
{
	char	buff[1024];
	int	len = 1;

	if (fd == -1){
		write(client->fd, "550 Permission denied\n", 22);
		return;
	}
	write(client->fd, client->data->fd == client->data->current->fd ? "125" : "150", 3);
	write(client->fd, " Sendind file...\n", 17);
	while (len > 0){
		len = read(fd, buff, 1023);
		buff[len] = 0;
		if (len > 0)
			write(client->data->current->fd, buff, len);
	}
	client->data->cdel(client->data);
	client->data = 0;
	write(client->fd, "226 File send\n", 14);
	close(fd);
}

void	retr(client_t *client, const char *argv)
{
	int	fd;
	char	*path;
	char	*filename;

	if (!client->data || !client->data->current){
		write(client->fd, "425 Use PORT or PASV before\n", 28);
		return;
	}
	path = root_path(client);
	filename = get_file_name(path, argv);
	if (path)
		free(path);
	if (!path || !filename){
		write(client->fd, "550 Impossible to read file\n", 28);
		return;
	}
	fd = open(filename, O_RDONLY);
	send_data(client, fd);
	free(filename);
}