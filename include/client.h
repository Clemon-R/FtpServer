/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** client
*/

#ifndef CLIENT_H_
	#define CLIENT_H_

	#include "command.h"
	#include "server.h"
	#include "directory.h"

struct server_s;
typedef struct server_s	server_t;

typedef struct	account_s
{
	const char	*user;
	char	logged;
}		account_t;

typedef struct	client_s
{
	int	fd;
	struct sockaddr_in	*s_in;
	server_t		*data;

	int	(*cnew)(struct client_s *client, int fd
			, struct sockaddr_in *);
	void	(*cdel)(struct client_s *client);
	void	(*handle_packet)(struct client_s *client);

	path_t		*current;

	server_t	*server;
	account_t	account;

	struct client_s	*prev;
	struct client_s	*next;
}		client_t;

client_t	*init_client(server_t *server, client_t *client);

#endif /* !CLIENT_H_ */
