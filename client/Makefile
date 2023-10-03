NAME = tpe_client

CC = gcc
CCFLAGS =

SRC = main.c \
	  connect_server.c \
	  init_bmp_header.c	\
	  recv_data_from_server.c \
	  send_data_to_server.c \
	  create_bmp.c \
	  main.c \
	  save_bmp_file.c \
	  utils.c

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
