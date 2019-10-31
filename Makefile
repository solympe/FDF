# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: solympe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 17:17:21 by solympe           #+#    #+#              #
#    Updated: 2019/10/31 17:17:25 by solympe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS =  -Wall -Wextra -Werror
LIBA1 = libft.a
LIBA2 = libmlx.a

FILES = rotate line_drawer map_reader FDF
SRC =  $(patsubst  %,srcs/%.c, $(FILES))
OBJECTS   =  $(patsubst %, %.o , $(FILES))

.PHONY: all fclean clean re relib

all: $(NAME)

$(NAME):
	@make re -C libft
	@clang $(CFLAGS) -c $(SRC)  -I libft/ -I ./
	@clang $(CFLAGS) $(OBJECTS) -I  libft/  -L. -lft -o $(NAME)
clean:
	rm -f $(OBJECTS)
	make clean -C libft
	make clean -C mlx

fclean: clean
	@rm -f $(NAME) $(LIB)

re: fclean all

relib:
	make re -C libft
