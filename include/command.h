/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** command
*/

#ifndef COMMAND_H_
	#define COMMAND_H_

	#define	NBR_COMMANDS	14

	#include "server.h"
	#include "client.h"

struct server_s;
struct client_s;
typedef struct server_s	server_t;
typedef struct client_s	client_t;


typedef struct	command_s
{
	char	*name;
	char	log;
	void	(*function)(client_t *client, const char *arg);
}		command_t;

command_t	*get_list(void);

void	handle_command(server_t *server, client_t *client, char *arg);

#endif /* !COMMAND_H_ */
