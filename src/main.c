/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** main
*/

#include "server.h"
#include "command.h"
#include "directory.h"
#include <stdio.h>
#include <ctype.h>

static void	usage(void)
{
	printf("USAGE: ./server port path\n");
	printf("\tport is the port number on which");
	printf(" the server socket listens\n");
	printf("\tpath is the path to the home directory");
	printf(" for the Anonymous user\n");
}

static char	check_error(int argc, char **argv)
{
	if (argc < 2 || argc > 3){
		fprintf(stderr, "Number of parameters incorrect\n");
		return (1);
	}
	else if (!dir_exist(argv[2])){
		fprintf(stderr, "Path root not found\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	server_t	*server = init_server();

	if (check_error(argc, argv))
		return (84);
	else if (strcasecmp(argv[1], "-help") == 0){
		usage();
		return (0);
	}
	if (!server){
		fprintf(stderr, "Impossible to initialise server\n");
		return (84);
	}
	server->cnew(server, argv[2], HOST);
	if (server->set_port(server, atoi(argv[1]), "0.0.0.0")){
		fprintf(stderr, "Port already use\n");
		return (84);
	}
	server->start(server);
	server->cdel(server);
	return (0);
}