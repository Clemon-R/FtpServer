/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** directory
*/

#include "directory.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

path_t	*create_path(char *name, path_t *parent)
{
	path_t	*path = malloc(sizeof(path_t));
	int	len = strlen(name);

	if (!path)
		return (0);
	path->parent = parent;
	path->name = name;
	if (name[len - 1] == '/')
		name[len - 1] = 0;
	if (*name == '/')
		name += 1;
	return (path);
}

char	*get_path(path_t *path)
{
	char	*new;
	char	*parent = 0;

	if (!path)
		return (0);
	if (path->parent)
		parent = get_path(path->parent);
	if (!parent)
		new = strdup(path->name);
	else{
		new = malloc(sizeof(char) * (strlen(parent) +
					strlen(path->name) + 2));
		strcpy(new, parent);
		strcat(new, "/");
		strcat(new, path->name);
		free(parent);
	}
	return (new);
}

void	delete_path(path_t *path)
{
	free(path->name);
	free(path);
}

void	delete_paths(path_t *path)
{
	path_t	*current = path;
	path_t	*tmp;

	while (current){
		tmp = current;
		current = current->parent;
		delete_path(tmp);
	}
}

char	dir_exist(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}