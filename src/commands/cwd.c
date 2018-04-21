/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** cwd
*/

#include "commands.h"
#include "directory.h"

static char	*root_path(client_t *client, const char *argv)
{
	int	root_len = strlen(client->server->root);
	char	*current = get_path(client->current);
	int	current_len = (current ? strlen(current) : 0);
	int	arg_len = (argv ? strlen(argv) : 0);
	char	*new = malloc(sizeof(char) *
	(root_len + current_len + arg_len + 3));

	strcpy(new, client->server->root);
	if (current){
		strcat(new, "/");
		strcat(new, current);
	}
	if (argv){
		strcat(new, "/");
		strcat(new, argv);
	}
	if (current)
		free(current);
	return (new);
}

static path_t	*decode_path(const char *argv)
{
	int	i = 0;
	char	*name = argv && *argv ? malloc(sizeof(argv) + 1) : 0;
	path_t	*current = 0;
	path_t	**link = 0;

	if (!name)
		return (0);
	name[0] = 0;
	for (i = 0;argv[i] && argv[i] != '/';i += 1)
		name[i] = argv[i];
	name[i] = 0;
	if (argv[i] == '/')
		current = decode_path(argv + i + 1);
	link = &current;
	while (*link && (*link)->parent)
		link = &(*link)->parent;
	link = current ? &((*link)->parent) : &current;
	if (*name)
		*link = create_path(name, 0);
	return (current);
}

static path_t	*back_to_parent(path_t *path)
{
	path_t	*current = path;
	path_t	*parent;
	path_t	*result = path;
	unsigned int	count = 0;

	while (current){
		parent = current->parent;
		if (count > 0 || strcmp(current->name, "..") == 0){
			result = result == current ? parent : result;
			count += strcmp(current->name, "..") == 0 ? 1 : -1;
			delete_path(current);
			if (result && result != parent)
				result->parent = parent;
		}
		current = parent;
	}
	return (result);
}

static char	*concat_str(const char *str1, const char *str2)
{
	char	*result = malloc(sizeof(char) * (
		(str1 ? strlen(str1) : 0) +
		(str2 ? strlen(str2) : 0) +
		2
	));

	if (!result)
		return (0);
	result[0] = 0;
	if (str1)
		strcat(result, str1);
	if (*result)
		strcat(result, "/");
	if (str2)
		strcat(result, str2);
	return (result);
}

void	cwd(client_t *client, const char *argv)
{
	char	*path;
	char	*tmp = get_path(client->current);
	char	*result = concat_str(tmp, argv);

	if (!argv){
		write(client->fd, "550 Impossible to change path\n", 30);
		return;
	}
	free(tmp);
	path = root_path(client, argv);
	if (path && dir_exist(path)){
		if (client->current)
			delete_paths(client->current);
		client->current = back_to_parent(decode_path(result));
		write(client->fd, "250 Path changed\n", 18);
	}
	else
		write(client->fd, "550 Impossible to change path\n", 30);
	free(result);
	free(path);
}