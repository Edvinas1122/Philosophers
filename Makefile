# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 14:49:54 by emomkus           #+#    #+#              #
#    Updated: 2022/02/04 18:05:16 by emomkus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAFS = -Wall -Werror -Wextra
FILES = main.c ft_atoi.c
OBJ = $(FILES:.c=.o)
OUT = philo

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAFS) $(OBJ) -lpthread -o $(OUT)
	rm $(OBJ)

$(OBJ):
	$(CC) $(CFLAFS)  -c $(FILES)

observe:
	$(CC) $(CFLAFS)  -c observation.c
	$(CC) $(CFLAFS) observation.o -lpthread -o test
	rm observation.o

fclean:
	rm $(OUT)