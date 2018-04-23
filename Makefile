##
## EPITECH PROJECT, 2018
## bootstrap
## File description:
## Makefile
##

SRC	=	$(addprefix src/,	\
		server1.c	\
		server2.c	\
		server3.c	\
		client.c	\
		command.c	\
		directory.c	\
		main.c)

SRC	+=	$(addprefix src/commands/,	\
		quit.c	\
		user.c	\
		pass.c	\
		pwd.c	\
		cwd.c	\
		cdup.c	\
		help.c	\
		dele.c	\
		pasv.c	\
		list.c	\
		retr.c	\
		port.c	\
		stor.c	\
		noop.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	server

CC	=	gcc

CFLAGS	+=	-Iinclude -g3

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all