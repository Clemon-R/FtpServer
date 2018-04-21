/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** directory
*/

#ifndef DIRECTORY_H_
	#define DIRECTORY_H_

typedef struct	path_s
{
	char		*name;

	struct path_s	*parent;
}		path_t;

path_t	*create_path(char *name, path_t *parent);
char	*get_path(path_t *path);
void	delete_path(path_t *path);
void	delete_paths(path_t *path);
char	dir_exist(const char *dir);

#endif /* !DIRECTORY_H_ */
