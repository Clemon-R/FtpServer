/*
** EPITECH PROJECT, 2018
** bootstrap
** File description:
** command
*/

#include "command.h"
#include "commands.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static command_t	list_of_commands[1];

static void		set_list2(command_t *list)
{
	list[11].name = "retr";
	list[11].log = 1;
	list[11].function = &retr;
	list[12].name = "port";
	list[12].log = 1;
	list[12].function = &port;
	list[13].name = "stor";
	list[13].log = 1;
	list[13].function = &stor;
}

static void		set_list1(command_t *list)
{
	list[4].name = "pwd";
	list[4].log = 1;
	list[4].function = &pwd;
	list[5].name = "cwd";
	list[5].log = 1;
	list[5].function = &cwd;
	list[6].name = "cdup";
	list[6].log = 1;
	list[6].function = &cdup;
	list[7].name = "help";
	list[7].log = 1;
	list[7].function = &help;
	list[8].name = "dele";
	list[8].log = 1;
	list[8].function = &dele;
	list[9].name = "pasv";
	list[9].log = 1;
	list[9].function = &pasv;
	set_list2(list);
}

command_t	*get_list(void)
{
	command_t	*commands = malloc(sizeof(command_t) * NBR_COMMANDS);

	commands[0].name = "noop";
	commands[0].log = 1;
	commands[0].function = &noop;
	commands[1].name = "quit";
	commands[1].log = 0;
	commands[1].function = &quit;
	commands[2].name = "user";
	commands[2].log = 0;
	commands[2].function = &user;
	commands[3].name = "pass";
	commands[3].log = 0;
	commands[3].function = &pass;
	commands[10].name = "list";
	commands[10].log = 1;
	commands[10].function = &list;
	set_list1(commands);
	return (commands);
}

void	handle_command(server_t *server, client_t *client, char *buff)
{
	int	pos = strcspn(buff, " ");
	char	command[5];
	char	*arg = strlen(buff) == pos ? 0 : buff + pos + 1;

	strncpy(command, buff, pos > 4 ? 0 : pos);
	command[pos > 4 ? 0 : pos] = 0;
	printf("Command (%s) : %s\n", command, arg);
	for (int i = 0;i < NBR_COMMANDS;i += 1){
		if (strcasecmp(server->list[i].name, command) == 0
		&& server->list[i].log <= client->account.logged){
			(*server->list[i].function)(client, arg);
			return;
		}
	}
	if (client->account.logged)
		write(client->fd, "500 Unknow command\n", 19);
	else
		write(client->fd, "530 Need to log in\n", 19);
}