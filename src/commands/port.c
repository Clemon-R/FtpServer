/*
** EPITECH PROJECT, 2018
** ftp
** File description:
** port
*/

#include "commands.h"

static char	*get_ip(const char *arg)
{
	char	*ip;

	if (!arg || !*arg)
		return (0);
	ip = malloc(sizeof(char) * (strlen(arg) + 1));
	if (!ip)
		return (0);
	for (int i = 0, counter = 0;arg[i] && counter < 4;i += 1){
		if (arg[i] == ',')
			counter += 1;
		if (counter == 4){
			strncpy(ip, arg, i);
			ip[i] = 0;
		}
	}
	for (int i = 0;ip[i];i += 1)
		if (ip[i] == ',')
			ip[i] = '.';
	return (ip);
}

static unsigned int	get_port(const char *ip, const char *arg)
{
	unsigned int	port = 0;
	const char	*port_arg;

	if (!ip || !*ip)
		return (port);
	port_arg = arg + strlen(ip) + 1;
	for (int i = 0;port_arg[i];i += 1){
		if (port_arg[i]  == ','){
			port = atoi(port_arg) * 256 + atoi(port_arg + i + 1);
			break;
		}
	}
	return (port);
}

static server_t	*creating_server(const char *ip, unsigned int port)
{
	server_t	*server;

	server = init_server();
	if (!server)
		return (0);
	server->cnew(server, 0, DATA);
	server->set_port(server, port, ip);
	return (server);
}

void	port(client_t *client, const char *argv)
{
	char		*ip = get_ip(argv);
	int		port;
	server_t	*server;

	if (!argv || !*argv || !ip)
		return;
	if (client->data)
		client->data->cdel(client->data);
	port = get_port(ip, argv);
	server = creating_server(ip, port);
	if (ip)
		free(ip);
	if (connect(server->fd
	, (struct sockaddr *)&server->s_in, sizeof(server->s_in)) == -1)
		return;
	handle_client(server, server->fd, &server->s_in);
	client->data = server;
	server->parent = client;
	write(client->fd, "200 Server connected\n", 21);
}