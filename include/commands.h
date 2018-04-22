/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** commands
*/

#ifndef COMMANDS_H_
	#define COMMANDS_H_

	#define USER	"Anonymous"
	#define PASS	""

	#include <unistd.h>
	#include <string.h>
	#include "client.h"

void	noop(client_t *client, const char *argv);
void	quit(client_t *client, const char *argv);
void	user(client_t *client, const char *argv);
void	pass(client_t *client, const char *argv);
void	pwd(client_t *client, const char *argv);
void	cwd(client_t *client, const char *argv);
void	cdup(client_t *client, const char *argv);
void	help(client_t *client, const char *argv);
void	dele(client_t *client, const char *argv);
void	pasv(client_t *client, const char *argv);
void	list(client_t *client, const char *argv);
void	retr(client_t *client, const char *argv);
void	port(client_t *client, const char *argv);

#endif /* !COMMANDS_H_ */
