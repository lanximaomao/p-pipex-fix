# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 13:20:08 by atoof             #+#    #+#              #
#    Updated: 2023/03/05 10:57:54 by linlinsun        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = free_pipex.c error_print.c child.c pipex.c
OBJ = $(SRC:.c=.o)
HEADER = pipex.h
LIBFT = ./libft/libft.a
FLAGS = -Wall -Werror -Wextra

all: $(OBJ) $(LIBFT)
	cc $(FLAGS) $(OBJ) -I$(HEADER) $(LIBFT) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
