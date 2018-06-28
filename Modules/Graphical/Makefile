##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME		= 	zappy_graphical

CC		= 	g++

SHARED		=	../Shared

GRAPHICAL	= 	Modules/GRAPHICAL

RM		= 	rm -f

SRCS_C		=	$(SHARED)/srcs/connection/sockets.c

OBJS_C		=	$(SRCS_C:.c=.o)

SRCS_CPP	= 	srcs/main.cpp					\
			srcs/Display/event.cpp				\
			srcs/Display/Game/communication.cpp		\
			srcs/Display/textureAndSprite.cpp		\
	  		srcs/Display/text.cpp				\
			srcs/Display/mouse.cpp				\
			srcs/Display/font.cpp				\
	  		srcs/Display/Menu/menu.cpp			\
	  		srcs/Display/Game/map.cpp			\
	  		srcs/Display/Game/game.cpp			\
	  		srcs/Display/Game/loop.cpp			\
			srcs/Display/Splash/intro.cpp			\
			srcs/Display/Players/players.cpp

OBJS_CPP	= 	$(SRCS_CPP:.cpp=.o)

CXXFLAGS 	= 	-I./includes/		\
			-I./includes/Sprite/	\
			-I$(SHARED)/includes/	\
			-W -Wextra -g3

LDFLAGS		= 	-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

.c.o:
			@$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ && \
			printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

.cpp.o:
			@$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ && \
			printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 			cclean $(NAME)
			cp $(NAME) ../..
			rm -f $(OBJS_C)

cclean:
			rm -f $(OBJS_C)

$(NAME):		$(OBJS_C) $(OBJS_CPP)
			@$(CC) $(OBJS_C) $(OBJS_CPP) $(CXXFLAGS) -o $(NAME) $(LDFLAGS) && \
			printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'


clean:
			@$(RM) $(OBJS_C) && \
			printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_C) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_C) | tr ' ' '.' && \
			$(RM) $(OBJS_CPP) && \
			printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_CPP) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_CPP) | tr ' ' '.'

fclean: 		clean
			@$(RM) $(NAME) && \
			printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
			$(RM) ../../$(NAME)

re:			 fclean all

.PHONY: 		all cclean clean fclean re
