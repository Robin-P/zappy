##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	= 	zappy_ai

CC	= 	gcc

SHARED	=	../Shared

AI	= 	Modules/AI

RM	= 	rm -f

SRCS	= 	./srcs/main.c					\
	  	./srcs/arguments/arguments.c			\
	  	./srcs/arguments/args_fct.c			\
	  	./srcs/server/connect.c				\
		./srcs/server/response.c			\
		./srcs/server/handle_response.c			\
		./srcs/ai/ai.c					\
		./srcs/ai/incantation.c				\
		./srcs/ai/begin_connection.c			\
		./srcs/ai/send_commands.c			\
		./srcs/ai/ai_list.c				\
		./srcs/ai/state_ai.c				\
		./srcs/ai/dump_list.c				\
		./srcs/ai/inventory.c				\
		$(SHARED)/srcs/connection/sockets.c		\
		$(SHARED)/srcs/tools/array_tools.c		\
		$(SHARED)/srcs/tools/count_row.c		\
		$(SHARED)/srcs/tools/string_tools.c		\
		$(SHARED)/srcs/tools/init_struct.c		\
		$(SHARED)/srcs/tools/get_next_line.c		\
		$(SHARED)/srcs/tools/string_strip.c		\
		$(SHARED)/srcs/tools/replace.c

OBJS	= 	$(SRCS:.c=.o)

CFLAGS = 	-I./includes/			\
	 	-I./includes/arguments/		\
		-I./includes/server		\
		-I./includes/connection		\
		-I./includes/client		\
		-I$(SHARED)/includes

CFLAGS += 	-W -Wall -Wextra

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 		$(NAME)
		cp $(NAME) ../..
		cp python_ai.sh ../../zappy_ai && chmod +x ../../zappy_ai

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'

clean:
		@$(RM) $(OBJS) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean: 	clean
		@$(RM) $(NAME) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
		$(RM) ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
