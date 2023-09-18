# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suhkim <suhkim@student.4seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 0/09/30 0:33:0 by suhkim            #+#    #+#              #
#    Updated: 2023/07/05 20:25:03 by suhkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = TPE

CC = gcc

CFLAGS =

SRC = create_bmp.c \
		 init_bmp_header.c \
		 inverse_round_n.c \
		 permutation.c \
		 save_bmp_file.c \
		 create_random_n_arr.c \
		 inverse_permutation.c \
		 main.c \
		 round.c \
		 substitution.c

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
