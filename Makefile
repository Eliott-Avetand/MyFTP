##
## EPITECH PROJECT, 2020
## myftp
## File description:
## Makefile
##

SRC	=	src/main.c								\
		src/my_ftp.c							\
		src/errors/errors.c						\
		src/utils/is_number.c					\
		src/utils/my_str_to_word_array.c		\
		src/utils/manage_client.c				\
		src/utils/double_array.c				\
		src/process/processing.c				\
		src/commands/pass.c						\
		src/commands/user.c						\
		src/commands/cwd.c						\
		src/commands/cdup.c						\
		src/commands/quit.c						\
		src/commands/dele.c						\
		src/commands/pwd.c						\
		src/commands/pasv.c						\
		src/commands/port.c						\
		src/commands/help.c						\
		src/commands/noop.c						\
		src/commands/retr.c						\
		src/commands/stor.c						\
		src/commands/list.c						\
		src/configuration/configure_server.c

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS  +=      -W -Wall -Wextra -Iinclude

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f vgcore*

re:	clean all

debug: fclean
	gcc -o $(NAME) $(SRC) $(CFLAGS) -g

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes ./$(NAME) 4242 /

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
