# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 14:25:22 by jbartosi          #+#    #+#              #
#    Updated: 2023/04/13 18:08:31 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

THREADS = -pthread
CFLAGS = -Wall -Wextra -Werror

SRC = philosophers.c philosophers_utils.c routines.c
OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(SRC)
	@cc -g $(CFLAGS) $(THREADS) -o $@ $^

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re:	fclean
	@make all

.PHONY: re, fclean, clean


