##
## EPITECH PROJECT, 2018
## server_zappy ()
## File description:
## Makefile
##
#PTDR Cest un Makefile

NAME		=	zappy_server

SERVER		=	Modules/Server

AI		=	Modules/AI

GRAPHICAL	=	Modules/Graphical

all: 		graphical server ai

server:
		make -C $(SERVER)

ai:
		make -C $(AI)

graphical:
		make -C $(GRAPHICAL)

clean:
		make clean -C $(GRAPHICAL)
		make clean -C $(AI)
		make clean -C $(SERVER)

fclean: 	clean
		make fclean -C $(GRAPHICAL)
		make fclean -C $(AI)
		make fclean -C $(SERVER)

re:		fclean all

.PHONY: 	all clean fclean re graphical server ai
