# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 14:49:54 by emomkus           #+#    #+#              #
#    Updated: 2022/02/07 16:47:36 by emomkus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAFS = -Wall -Werror -Wextra -fsanitize=address
FILES = main.c ft_atoi.c thread.c input_formation.c start_threads.c 
OBJ = $(FILES:.c=.o)
OUT = philo

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAFS) $(OBJ) -lpthread -o $(OUT)
	rm $(OBJ)

$(OBJ):
	$(CC) $(CFLAFS)  -c $(FILES)

fclean:
	rm $(OUT)