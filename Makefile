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

SRC = map_reader.c line_drawer.c rotate.c fdf.c kill_me.c

OBJ = map_reader.o line_drawer.o rotate.o fdf.o kill_me.o

HEADER = fdf.h

$(NAME): $(OBJ)
	@make -C libft/
	@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -L libft -lft -L ./mlx/ -lmlx -framework OpenGL -framework AppKit 

%.o:%.c $(HEADER)
	@gcc -Wall -Wextra -Werror -I . -c $< -o $@

clean:
	@/bin/rm -f *~
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re
