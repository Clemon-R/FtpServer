/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** server
*/

#ifndef SERVER_H_
	#define SERVER_H_

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>
	#include <stdio.h>
	#include <sys/time.h>
	#include "client.h"
	#include "command.h"

struct command_s;
struct client_s;
typedef struct command_s	command_t;
typedef struct client_s		client_t;

enum	SERVER_TYPE
{
	HOST,
	DATA
};

typedef struct	server_s
{
	int			fd;
	struct protoent		*pe;
	struct sockaddr_in	s_in;
	enum SERVER_TYPE	type;
	unsigned int		data_port;

	char			*root;

	client_t		*current;
	client_t		*last;
	client_t		*parent;

	command_t		*list;

	int	(*cnew)(struct server_s *server, char *root
			, enum SERVER_TYPE);
	void	(*cdel)(struct server_s *server);

	int	(*set_port)(struct server_s *server, unsigned int port
				, const char *ip);
	int	(*start)(struct server_s *server);
}		server_t;

server_t	*init_server();

int	set_port(server_t *server, unsigned int port, const char *ip);
int	create_socket(server_t *server, char *root, enum SERVER_TYPE);
void	close_socket(server_t *server);
int	start_server(server_t *server);
void	handle_client(server_t *server, int client_fd
			, struct sockaddr_in *);
int	get_the_highest_fd(server_t *server);
void	set_fdset(server_t *server, fd_set *readfts);
void	handle_main(server_t *server);
void	handle_packet_s(server_t *server, fd_set *readfts);

#endif /* !SERVER_H_ */
